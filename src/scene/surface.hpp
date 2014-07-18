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

#ifndef __SURFACE_H_INCLUDE__
#define __SURFACE_H_INCLUDE__


class Surface {
protected:
    GLuint id;

    Matrix<f32, 4, 4> modelMatrix;

    shared_ptr<ShaderProgram> program;


    virtual void renderImpl(const shared_ptr<Renderer> &renderer) = 0;


public:
    Surface();
    Surface(const shared_ptr<ShaderProgram> &program);
    virtual ~Surface();


    virtual void animate(f64 t, f64 dt);
    virtual void render(const shared_ptr<Renderer> &renderer);
};


class FlatSurface : public Surface {
protected:
    VertexAttributeBufferV<f32, 2> vertices;

    ElementBuffer<i8u, 3> triangles;


    void setup();

    virtual void renderImpl(const shared_ptr<Renderer> &renderer);


public:
    FlatSurface();
    FlatSurface(const shared_ptr<ShaderProgram> &program);
    virtual ~FlatSurface();


    virtual void animate(f64 t, f64 dt);
};


#endif //__SURFACE_H_INCLUDE__