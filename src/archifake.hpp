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

#ifndef __ARCHIFAKE_H_INCLUDE__
#define __ARCHIFAKE_H_INCLUDE__


// system headers
//#include <typeinfo>
#include <math.h>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <wchar.h>
//#include <stdarg.h>
//#include <pthread.h>
#include <errno.h>
//#include <unistd.h>
//#include <dirent.h>
//#include <sys/stat.h>

#include <X11/X.h>
//#include <X11/Xlib.h>
//#include <X11/Xutil.h>
//#include <X11/Xft/Xft.h>

#include <GL/glew.h>
#include <GL/glx.h>
#include <GL/glxext.h>
#include <GL/gl.h>

#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>

using namespace std;


// basic numeric types
typedef signed char             i8;
typedef unsigned char           i8u;

typedef signed short            i16;
typedef unsigned short          i16u;

typedef signed int              i32;
typedef unsigned int            i32u;

typedef signed long long        i64;
typedef unsigned long long      i64u;

typedef float                   f32;
typedef double                  f64;


// macros
#define MIN(a, b)  ((a) < (b) ? (a) : (b))


// program headers
#include "utils/clock.hpp"
#include "utils/math.hpp"
#include "utils/buffer.hpp"
#include "scene/surface.hpp"
#include "scene/scene.hpp"
#include "window.hpp"


#endif //__ARCHIFAKE_H_INCLUDE__