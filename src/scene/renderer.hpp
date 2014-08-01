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

#ifndef __RENDERER_H_INCLUDE__
#define __RENDERER_H_INCLUDE__


class Renderer {
public:
    Camera camera;


    Renderer() {
    }

    virtual ~Renderer() {
    }


    virtual i32 width() const = 0;

    virtual i32 height() const = 0;

    f32 ratio() const {
        if (this->height() > 0) {
            return (f32)this->width() / (f32)this->height();
        }
        return 1.0f;
    }


    virtual void beginFrame() = 0;
    virtual void endFrame() = 0;
};


#endif //__RENDERER_H_INCLUDE__