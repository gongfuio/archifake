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

    // create window
    if (!window.create()) {
        fprintf(stderr, "ERROR: Cannot create window!\n");
    }
    if (!window.activate()) {
        fprintf(stderr, "ERROR: Cannot activate window!\n");
    }

    // setup glew
    glewInit();

    // setup demo scene
    shared_ptr<ShaderProgram> program(
        new ShaderProgram(
            Shader::fromFile(GL_VERTEX_SHADER, "test.vs"),
            Shader::fromFile(GL_FRAGMENT_SHADER, "test.fs")
        )
    );
    shared_ptr<Surface> surface0(new FlatSurface(program));
    Scene scene;

    // program->print();

    scene.addSurface("surface0", surface0);
    scene.startAll();
    scene.showAll();

    // setup demo renderer
    shared_ptr<Renderer> renderer(new Renderer());

    renderer->camera.projectionMatrix = PerspectiveProjection<f32>(60.0 / 180.0 * M_PI, window.ratio(), 0.01, 100.0);
    renderer->camera.viewMatrix = LookAtTransform<f32>(Vector3<f32>(0, 0.25, 1), Vector3<f32>(0, 0, 0), Vector3<f32>(0, 1, 0));

    // event loop
    i64u firstDraw, lastDraw;

    firstDraw = Clock::tick();
    lastDraw = Clock::tick();
    while (window.exists()) {
        bool draw = Clock::elapsed(lastDraw) >= frameTime;
        bool active = false;

        if (draw) {
            renderer->camera.viewport = Rectangle2<i32>(0, 0, window.width(), window.height());
            renderer->camera.projectionMatrix = PerspectiveProjection<f32>(60.0 / 180.0 * M_PI, window.ratio(), 0.01, 100.0);
            // renderer->camera.viewMatrix = LookAroundYTransform<f32>(Vector3<f32>(0, 0, 0), 10.0, Clock::elapsed(firstDraw) * M_PI * 2, 0);
            // renderer.animate();

            lastDraw = Clock::tick();
            window.beginFrame(renderer->camera);
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

    // setup clock
    Clock::setup();

    // execute program
    run(display, screen);

    // close display
    XCloseDisplay(display);
    return 0;
}