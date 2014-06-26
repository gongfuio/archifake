#include <typeinfo>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <wchar.h>
#include <stdarg.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xft/Xft.h>

#include <GL/glew.h>
#include "GL/glx.h"
#include "GL/glxext.h"


int main(int argc, char **argv) {
	auto display = XOpenDisplay(getenv("DISPLAY"));
	auto screenIndex = 0;
	auto screen = XScreenOfDisplay(display, screenIndex);
	auto screenWidth = XDisplayWidth(display, screenIndex);
	auto screenHeight = XDisplayHeight(display, screenIndex);


	int errorBase = 0;
	int eventBase = 0;

	if (!glXQueryExtension(display, &errorBase, &eventBase)) {
		return 1;
	}


	GLint glxAttrs[] = {
		GLX_RENDER_TYPE,		GLX_RGBA_BIT,
		GLX_DRAWABLE_TYPE,		GLX_WINDOW_BIT,
		GLX_TRANSPARENT_TYPE,	GLX_NONE,
		GLX_X_RENDERABLE,		GLX_DONT_CARE,
		GLX_X_VISUAL_TYPE,		GLX_TRUE_COLOR,
		GLX_DOUBLEBUFFER,		True,
		GLX_STEREO,				False,
		GLX_BUFFER_SIZE,		32,
		GLX_RED_SIZE,			8,
		GLX_GREEN_SIZE,			8,
		GLX_BLUE_SIZE,			8,
		GLX_ALPHA_SIZE,			8,
		GLX_DEPTH_SIZE,			24,
		GLX_STENCIL_SIZE,		8,
		GLX_AUX_BUFFERS,		0,
		GLX_SAMPLE_BUFFERS,		0,
		GLX_SAMPLES,			0,
		GLX_ACCUM_RED_SIZE,		0,
		GLX_ACCUM_GREEN_SIZE,	0,
		GLX_ACCUM_BLUE_SIZE,	0,
		GLX_ACCUM_ALPHA_SIZE,	0,
		None
	};
	int nbconfigs = 0;
	auto glxConfig = glXChooseFBConfig(display, screenIndex, glxAttrs, &nbconfigs);

	if (glxConfig == NULL || nbconfigs < 1) {
		return 2;
	}


	auto visualinfo = glXGetVisualFromFBConfig(display, glxConfig[0]);

	if (visualinfo == NULL) {
		return 3;
	}


	XSetWindowAttributes attrs;

	attrs.colormap = XCreateColormap(display, XRootWindowOfScreen(screen), visualinfo->visual, AllocNone);
	attrs.event_mask = StructureNotifyMask | ExposureMask | VisibilityChangeMask | EnterWindowMask | LeaveWindowMask | PointerMotionMask | ButtonPressMask | ButtonReleaseMask | KeyPressMask | KeyReleaseMask;
//	attrs.cursor = None;

	auto window = XCreateWindow(
		display,
		XRootWindowOfScreen(screen),
		0,
		0,
		screenWidth,
		screenHeight,
		0, // border width
		visualinfo->depth,
		InputOutput,
		visualinfo->visual,
		CWEventMask | CWColormap, // CWCursor
		&attrs
	);

	if (window == None) {
		return 4;
	}

	auto WM_DELETE_WINDOW = XInternAtom(display, "WM_DELETE_WINDOW", false);

	XSetWMProtocols(display, window, &WM_DELETE_WINDOW, 1);

	XMapWindow(display, window);

	auto glxSurface = glXCreateWindow(display, glxConfig[0], window, NULL);

	if (glxSurface == None) {
		return 5;
	}

	auto glxContext = glXCreateNewContext(display, glxConfig[0], GLX_RGBA_TYPE, NULL, True);

	if (glxContext == NULL) {
		return 6;
	}

	if (!glXMakeContextCurrent(display, glxSurface, glxSurface, glxContext)) {
		return 7;
	}


	bool quit = false;

	while (!quit) {
		glClearColor(0, 0, 0, 0);
		// glClearDepthf(this->value);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		while (XPending(display)) {
			XEvent xev;
			KeySym symbol;
			char buffer[2];

			XNextEvent(display, &xev);
			switch (xev.type) {
			case CirculateNotify:
				break;
			case ConfigureNotify:
				// 	this->_frame.left = event->xconfigure.x;
				// 	this->_frame.top = event->xconfigure.y;
				// 	this->_frame.width = event->xconfigure.width;
				// 	this->_frame.height = event->xconfigure.height;
				break;
			case DestroyNotify:
				quit = true;
				break;
			case GravityNotify:
				break;
			case ReparentNotify:
				break;
			case MapNotify:
				break;
			case UnmapNotify:
				break;

			case VisibilityNotify:
				switch (xev.xvisibility.state) {
				case VisibilityUnobscured:
					break;
				case VisibilityFullyObscured:
					break;
				case VisibilityPartiallyObscured:
					break;
				}
				break;

			case EnterNotify:
				break;
			case LeaveNotify:
				break;

			case MotionNotify:
				//this->convertMouse(event->xmotion.state), event->xmotion.x, event->xmotion.y;
				break;
			case ButtonPress:
				//this->convertMouse(event->xmotion.state), event->xbutton.x, event->xbutton.y, this->convertButton(event->xbutton.button)
				break;
			case ButtonRelease:
				//this->convertMouse(event->xmotion.state), event->xbutton.x, event->xbutton.y, this->convertButton(event->xbutton.button)
				break;
			case KeyPress:
				if (XLookupString(&xev.xkey, buffer, sizeof(buffer) - 1, &symbol, NULL) > 0) {
					if (buffer[0] >= 0x20 && buffer[0] != 0x7f) {
						char c = buffer[0];
					} else {
						// this->convertKey(symbol)
					}
				} else {
					// this->convertKey(symbol)
				}
				break;
			case KeyRelease:
				if (XLookupString(&xev.xkey, buffer, sizeof(buffer) - 1, &symbol, NULL) > 0) {
					if (buffer[0] >= 0x20 && buffer[0] != 0x7f) {
						char c = buffer[0];
					} else {
						// this->convertKey(symbol)
					}
				} else {
					// this->convertKey(symbol)
				}
				break;

			case ClientMessage:
				if (xev.xclient.data.l[0] == WM_DELETE_WINDOW) {
					quit = true;
				}
				break;
			}
		}

		// glFinish();
		glXSwapBuffers(display, glxSurface);
	}


	glXMakeContextCurrent(display, None, None, NULL);

	glXDestroyContext(display, glxContext);

	glXDestroyWindow(display, glxSurface);

	XFree(visualinfo);

	XFree(glxConfig);

	XUnmapWindow(display, window);

	XDestroyWindow(display, window);

	return 0;
}