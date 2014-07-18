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


Surface::Surface() : id(GL_ZERO), modelMatrix(IdentityTransform<f32>()) {
    glGenVertexArrays(1, &this->id);
}

Surface::Surface(const shared_ptr<ShaderProgram> &program) : id(GL_ZERO), modelMatrix(IdentityTransform<f32>()), program(program) {
    glGenVertexArrays(1, &this->id);
}

Surface::~Surface() {
    if (this->id != GL_ZERO) {
        glDeleteVertexArrays(1, &this->id);
    }
}

void Surface::animate(f64 t, f64 dt) {
}

void Surface::render(const shared_ptr<Renderer> &renderer) {
    const Matrix<f32, 4, 4> & pMatrix = renderer->camera.projectionMatrix;
    const Matrix<f32, 4, 4> & vMatrix = renderer->camera.viewMatrix;
    const Matrix<f32, 4, 4> pvMatrix(vMatrix * pMatrix);
    const Matrix<f32, 4, 4> pvmMatrix(this->modelMatrix * pvMatrix);

    this->program->enable();

    this->program->uniform("pMatrix", pMatrix);
    this->program->uniform("vMatrix", vMatrix);
    this->program->uniform("pvMatrix", pvMatrix);
    this->program->uniform("pvmMatrix", pvmMatrix);

    this->renderImpl(renderer);

    this->program->disable();
}


FlatSurface::FlatSurface() : Surface(), vertices(4), triangles(2) {
    this->setup();
}

FlatSurface::FlatSurface(const shared_ptr<ShaderProgram> &program) : Surface(program), vertices(4), triangles(2) {
    this->setup();
}

FlatSurface::~FlatSurface() {
}

void FlatSurface::setup() {
    this->vertices.setVertex(0, Vector2<f32>( 0.5,  0.5));
    this->vertices.setVertex(1, Vector2<f32>(-0.5,  0.5));
    this->vertices.setVertex(2, Vector2<f32>(-0.5, -0.5));
    this->vertices.setVertex(3, Vector2<f32>( 0.5, -0.5));

    this->triangles.setFace(0, {0, 1, 2});
    this->triangles.setFace(1, {2, 3, 0});

    if (this->id == GL_ZERO) {
        return;
    }
    glBindVertexArray(this->id);


    GLint inPosition = this->program->attributeLocation("inPosition");

    if (inPosition >= 0) {
        this->vertices.enable();
        glEnableVertexAttribArray(inPosition);
        // glVertexAttribDivisor(inPosition, 0);
        glVertexAttribPointer(
            inPosition,
            2,
            GL_FLOAT,
            GL_FALSE,
            0,
            reinterpret_cast<GLvoid*>(0)
        );
        this->vertices.disable();
    }

    this->triangles.enable();

    glBindVertexArray(GL_ZERO);

    this->triangles.disable();

    glDisableVertexAttribArray(inPosition);
}

void FlatSurface::renderImpl(const shared_ptr<Renderer> &renderer) {
    if (this->id == GL_ZERO) {
        return;
    }

    // glDisable(GL_SCISSOR_TEST);
    // glDisable(GL_STENCIL_TEST);
    // glDisable(GL_DEPTH_TEST);
    // glDisable(GL_CULL_FACE);
    // glCullFace(GL_FRONT_AND_BACK);

    glBindVertexArray(this->id);

    glDrawElements(
        GL_TRIANGLES,
        2 * 3,
        GL_UNSIGNED_BYTE,
        reinterpret_cast<GLvoid*>(0)
    );

    glBindVertexArray(GL_ZERO);
}

void FlatSurface::animate(f64 t, f64 dt) {
    // this->modelMatrix = RotateYTransform<f32>(t * M_PI);
}
