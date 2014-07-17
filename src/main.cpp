/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.


    Authors:
    -------

    Antony Ducommun <nitro@tmsrv.org>

*/

#include "archifake.hpp"


static const f64 frameTime = 1.0 / 60.0;


void run(Display *display, Screen *screen) {
    GLWindow window(display, screen);
    i64u lastDraw;
    Scene scene;

    // create window
    if (!window.create()) {
        fprintf(stderr, "ERROR: Cannot create window!\n");
    }
    if (!window.activate()) {
        fprintf(stderr, "ERROR: Cannot activate window!\n");
    }

    // setup clock
    Clock::setup();

    // setup demo scene
    const char *vertexShaderSource =
        R"(#version 420 core

        uniform mat4 pvmMatrix;
        in vec3 inPosition;

        void main(void) {
            gl_Position = pvmMatrix * vec4(inPosition, 1.0);
        }
        )";
    shared_ptr<Shader> vertexShader(new Shader(GL_VERTEX_SHADER, vertexShaderSource));
    const char *fragmentShaderSource =
        R"(#version 420 core

        out vec4 gl_FragColor;

        void main(void) {
            gl_FragColor = rgba(1.0, 1.0, 1.0, 1.0);
        }
        )";
    shared_ptr<Shader> fragmentShader(new Shader(GL_FRAGMENT_SHADER, fragmentShaderSource));
    shared_ptr<ShaderProgram> program(new ShaderProgram(vertexShader, fragmentShader));
    shared_ptr<Surface> surface0(new FlatSurface(program));
    shared_ptr<Renderer> renderer(new Renderer());

    scene.addSurface("surface0", surface0);

    printf("vertexShader: %s\n", vertexShader->getLogs().c_str());
    printf("fragmentShader: %s\n", fragmentShader->getLogs().c_str());
    printf("program(linker): %s\n", program->getLinkerLogs().c_str());
    printf("program(validator): %s\n", program->getValidatorLogs().c_str());

    // event loop
    lastDraw = Clock::tick();
    while (window.exists()) {
        bool draw = Clock::elapsed(lastDraw) >= frameTime;
        bool active = false;

        if (draw) {
            lastDraw = Clock::tick();
            window.beginFrame();
            scene.animate();
            scene.render(renderer);
        }
        while (XPending(display)) {
            XEvent xev;

            XNextEvent(display, &xev);
            window.processEvent(xev);
            active = true;
        }
        if (draw) {
            window.endFrame();
        } else if (!active) {
            f64 wait = frameTime - Clock::elapsed(lastDraw);

            if (wait > 0) {
                Clock::sleep(wait < 0.010 ? wait : 0.010);
            }
        }
    }

    // destroy window
    window.deactivate();
    window.destroy();
}


int main(int argc, char **argv) {
    // open display & screen
    auto display = XOpenDisplay(getenv("DISPLAY"));
    auto screen = XScreenOfDisplay(display, 0);

    if (display == NULL) {
        fprintf(stderr, "ERROR: Invalid display!\n");
        return 1;
    }
    if (screen == NULL) {
        fprintf(stderr, "ERROR: Invalid screen!\n");
        return 1;
    }

    // execute program
    run(display, screen);

    // close display
    XCloseDisplay(display);
    return 0;
}