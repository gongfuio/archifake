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


bool GLWindow::exists() {
    return this->window != None;
}

bool GLWindow::create() {
    GLint glxAttrs[] = {
        GLX_RENDER_TYPE,        GLX_RGBA_BIT,
        GLX_DRAWABLE_TYPE,      GLX_WINDOW_BIT,
        GLX_TRANSPARENT_TYPE,   GLX_NONE,
        // GLX_X_RENDERABLE,    True,
        GLX_X_VISUAL_TYPE,      GLX_TRUE_COLOR,
        GLX_DOUBLEBUFFER,       True,
        GLX_STEREO,             False,
        GLX_BUFFER_SIZE,        32,
        GLX_RED_SIZE,           8,
        GLX_GREEN_SIZE,         8,
        GLX_BLUE_SIZE,          8,
        GLX_ALPHA_SIZE,         8,
        GLX_DEPTH_SIZE,         24,
        GLX_STENCIL_SIZE,       8,
        GLX_AUX_BUFFERS,        0,
        GLX_SAMPLE_BUFFERS,     0,
        GLX_SAMPLES,            0,
        GLX_ACCUM_RED_SIZE,     0,
        GLX_ACCUM_GREEN_SIZE,   0,
        GLX_ACCUM_BLUE_SIZE,    0,
        GLX_ACCUM_ALPHA_SIZE,   0,
        None
    };
    int glxConfigCount = 0;

    // destroy existing window if any
    this->destroy();

    // check opengl support
    if (!glXQueryExtension(this->display, NULL, NULL)) {
        fprintf(stderr, "ERROR: OpenGL not supported!\n");
        return false;
    }

    // find compatible opengl framebuffer configurations
    this->glxConfigs = glXChooseFBConfig(
        this->display,
        XScreenNumberOfScreen(this->screen),
        glxAttrs,
        &glxConfigCount
    );
    if (this->glxConfigs == NULL || glxConfigCount == 0) {
        fprintf(stderr, "ERROR: No OpenGL framebuffer configuration is compatible!\n");
        return false;
    }

    // create opengl context
    this->glxContext = glXCreateNewContext(
        this->display,
        this->glxConfigs[0],
        GLX_RGBA_TYPE,
        NULL,
        True
    );
    if (this->glxContext == NULL) {
        fprintf(stderr, "ERROR: Cannot create OpenGL context!\n");
        return false;
    }

    // select first compatible configuration
    this->visualinfo = glXGetVisualFromFBConfig(this->display, this->glxConfigs[0]);
    if (this->visualinfo == NULL) {
        fprintf(stderr, "ERROR: OpenGL framebuffer configuration failed!\n");
        return false;
    }

    // create colormap
    this->colormap = XCreateColormap(
        this->display,
        XRootWindowOfScreen(this->screen),
        this->visualinfo->visual,
        AllocNone
    );
    if (this->colormap == None) {
        fprintf(stderr, "ERROR: Cannot create colormap!\n");
        return false;
    }

    // create window
    XSetWindowAttributes attrs;

    attrs.colormap = this->colormap;
    attrs.event_mask = StructureNotifyMask | ExposureMask | VisibilityChangeMask |
        EnterWindowMask | LeaveWindowMask | PointerMotionMask | ButtonPressMask |
        ButtonReleaseMask | KeyPressMask | KeyReleaseMask;
    attrs.cursor = None;

    this->_width = XDisplayWidth(this->display, XScreenNumberOfScreen(this->screen));
    this->_height = XDisplayHeight(this->display, XScreenNumberOfScreen(this->screen));

    this->window = XCreateWindow(
        this->display,
        XRootWindowOfScreen(this->screen),
        0,
        0,
        this->_width,
        this->_height,
        0, // border width
        this->visualinfo->depth,
        InputOutput,
        this->visualinfo->visual,
        CWEventMask | CWColormap, // | CWCursor,
        &attrs
    );
    if (this->window == None) {
        fprintf(stderr, "ERROR: Cannot create window!\n");
        return false;
    }

    // create opengl framebuffer
    this->glxWindow = glXCreateWindow(
        this->display,
        this->glxConfigs[0],
        this->window,
        NULL
    );
    if (this->glxWindow == None) {
        fprintf(stderr, "ERROR: Cannot create OpenGL framebuffer!\n");
        return false;
    }

    // register window manager close event
    this->wm_delete_window = XInternAtom(this->display, "WM_DELETE_WINDOW", false);
    if (this->wm_delete_window == None) {
        fprintf(stderr, "ERROR: Cannot create WM_DELETE_WINDOW atom!\n");
        return false;
    }
    XSetWMProtocols(display, window, &this->wm_delete_window, 1);

    // show window
    XMapWindow(this->display, this->window);
    return true;
}

void GLWindow::processEvent(XEvent &xev) {
    KeySym symbol;
    char buffer[2];

    // check if event belongs to this window
    if (!this->exists() || xev.xany.window != this->window) {
        return;
    }

    // process event
    switch (xev.type) {
    // case CirculateNotify:
    //     break;
    // case GravityNotify:
    //     break;
    // case ReparentNotify:
    //     break;
    // case VisibilityNotify:
    //     switch (xev.xvisibility.state) {
    //     case VisibilityUnobscured:
    //         break;
    //     case VisibilityFullyObscured:
    //         break;
    //     case VisibilityPartiallyObscured:
    //         break;
    //     }
    //     break;

    case MapNotify:
        this->visible = true;
        break;
    case ConfigureNotify:
        this->x = xev.xconfigure.x;
        this->y = xev.xconfigure.y;
        this->_width = xev.xconfigure.width;
        this->_height = xev.xconfigure.height;
        break;
    case UnmapNotify:
        this->visible = false;
        break;

    case EnterNotify:
        this->mouse = true;
        break;
    case MotionNotify:
        if (this->mouse) {
            this->mouseX = xev.xmotion.x;
            this->mouseY = xev.xmotion.y;
        }
        break;
    case ButtonPress:
        if (this->mouse) {
            this->mouseX = xev.xbutton.x;
            this->mouseY = xev.xbutton.y;

            // TODO: store mouse down
            // this->convertMouse(xev.xmotion.state)
            // this->convertButton(xev.xbutton.button)
            this->destroy();
        }
        break;
    case ButtonRelease:
        if (this->mouse) {
            this->mouseX = xev.xbutton.x;
            this->mouseY = xev.xbutton.y;

            // TODO: store mouse up
            // this->convertMouse(xev.xmotion.state)
            // this->convertButton(xev.xbutton.button)
        }
        break;
    case LeaveNotify:
        this->mouse = false;
        break;

    case KeyPress:
        if (XLookupString(&xev.xkey, buffer, sizeof(buffer) - 1, &symbol, NULL) > 0) {
            if (buffer[0] >= 0x20 && buffer[0] != 0x7f) {
                // TODO: store character
                // char c = buffer[0];
            } else {
                // TODO: store key down
                // this->convertKey(symbol)
            }
        } else {
            // TODO: store key down
            // this->convertKey(symbol)
        }
        break;
    case KeyRelease:
        if (XLookupString(&xev.xkey, buffer, sizeof(buffer) - 1, &symbol, NULL) > 0) {
            if (buffer[0] >= 0x20 && buffer[0] != 0x7f) {
                // TODO: store character
                // char c = buffer[0];
            } else {
                // TODO: store key up
                // this->convertKey(symbol)
            }
        } else {
            // TODO: store key up
            // this->convertKey(symbol)
        }
        break;

    case ClientMessage:
        if ((Atom)xev.xclient.data.l[0] == this->wm_delete_window) {
            this->destroy();;
        }
        break;
    case DestroyNotify:
        this->destroy();
        break;
    }
}

void GLWindow::destroy() {
    // hide window
    if (this->window != None) {
        XUnmapWindow(this->display, this->window);
    }

    // destroy opengl framebuffer
    if (this->glxWindow != None) {
        glXDestroyWindow(this->display, this->glxWindow);
        this->glxWindow = None;
    }

    // destroy window
    if (this->window != None) {
        XDestroyWindow(this->display, this->window);
        this->window = None;
    }

    // destroy colormap
    if (this->colormap != None) {
        XFreeColormap(this->display, this->colormap);
        this->colormap = None;
    }

    // destroy framebuffer configuration
    if (this->visualinfo != NULL) {
        XFree(this->visualinfo);
        this->visualinfo = NULL;
    }

    // destroy opengl context
    if (this->glxContext != NULL) {
        glXDestroyContext(this->display, this->glxContext);
        this->glxContext = NULL;
    }

    // free opengl framebuffer configurations
    if (this->glxConfigs != NULL) {
        XFree(this->glxConfigs);
        this->glxConfigs = NULL;
    }

    this->visible = false;
    this->x = this->y = 0;
    this->_width = this->_height = 0;
    this->mouse = false;
    this->mouseX = this->mouseY = 0;
}

bool GLWindow::activate() {
    if (this->glxContext == NULL || this->glxWindow == None || !glXMakeContextCurrent(this->display, this->glxWindow, this->glxWindow, this->glxContext)) {
        return false;
    }
    return true;
}

void GLWindow::beginFrame(const Camera &camera) {
    if (this->glxContext != NULL && glXGetCurrentContext() == this->glxContext) {
        glViewport(
            camera.viewport.tl[0],
            camera.viewport.tl[1],
            camera.viewport.width(),
            camera.viewport.height()
        );
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClearDepth(0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}

void GLWindow::endFrame() {
    if (this->glxContext != NULL && glXGetCurrentContext() == this->glxContext) {
        glFlush();
        glXSwapBuffers(this->display, this->glxWindow);
    }
}

void GLWindow::deactivate() {
    if (this->glxContext != NULL && glXGetCurrentContext() == this->glxContext) {
        glXMakeContextCurrent(this->display, None, None, NULL);
    }
}
