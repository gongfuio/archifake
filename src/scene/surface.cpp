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


void Surface::animate(f64 t, f64 dt) {
}

void Surface::render(const shared_ptr<Renderer> &renderer) {
}


FlatSurface::FlatSurface(const shared_ptr<ShaderProgram> &program) : Surface(), program(program), vertices(4), triangles(2) {
    this->vertices.setVertex(0, Vector2<double>( 0.5,  0.5));
    this->vertices.setVertex(1, Vector2<double>(-0.5,  0.5));
    this->vertices.setVertex(2, Vector2<double>(-0.5, -0.5));
    this->vertices.setVertex(3, Vector2<double>( 0.5, -0.5));

    this->triangles.setFace(0, {0, 1, 2});
    this->triangles.setFace(1, {2, 3, 0});
}

FlatSurface::~FlatSurface() {
}

void FlatSurface::animate(f64 t, f64 dt) {
}

void FlatSurface::render(const shared_ptr<Renderer> &renderer) {
    this->vertices.enable();
    this->triangles.enable();
    this->program->enable();

    this->program->disable();
    this->triangles.disable();
    this->vertices.disable();
}
