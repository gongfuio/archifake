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

#ifndef __WINDOW_H_INCLUDE__
#define __WINDOW_H_INCLUDE__


class GLWindow : public Renderer {
protected:
    Display *display;
    Screen *screen;
    GLXFBConfig *glxConfigs;
    GLXContext glxContext;
    XVisualInfo *visualinfo;
    Colormap colormap;
    Window window;
    GLXWindow glxWindow;
    Atom wm_delete_window;
    bool visible;
    i32 x, y;
    i32u _width, _height;
    bool mouse;
    i32 mouseX, mouseY;


public:
    GLWindow(Display *display, Screen *screen) : Renderer(), display(display), screen(screen), glxConfigs(NULL), glxContext(NULL), visualinfo(NULL), colormap(None), window(None), glxWindow(None), wm_delete_window(None), visible(false), x(0), y(0), _width(0), _height(0), mouse(false), mouseX(0), mouseY(0) {
    }

    virtual ~GLWindow() {
        this->destroy();
    }


    virtual i32 width() const {
        return this->_width;
    }

    virtual i32 height() const {
        return this->_height;
    }


    bool exists();
    bool create();
    void processEvent(XEvent &xev);
    void destroy();

    bool activate();
    void deactivate();

    void beginFrame();
    void endFrame();
};


#endif //__WINDOW_H_INCLUDE__