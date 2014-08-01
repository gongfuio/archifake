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

#ifndef __CAMERA_H_INCLUDE__
#define __CAMERA_H_INCLUDE__


class Camera {
public:
    typedef Matrix<f32, 4, 4> M;


protected:
    M _projectionMatrix;
    M _viewMatrix;


public:
    LazyInitialized<M> projectionViewMatrix;
    LazyInitialized<M> projectionMatrixInverse;
    LazyInitialized<M> viewMatrixInverse;
    LazyInitialized<M> projectionViewMatrixInverse;
    Rectangle2<i32> viewport;
    Range<f64> depthRange;
    RGBA<f32> clearColor;
    f64 clearDepth;
    i32 clearStencil;


    Camera() : _projectionMatrix(IdentityTransform<f32>()), _viewMatrix(IdentityTransform<f32>()),
        projectionViewMatrix(
            [] (M &mat) { mat = IdentityTransform<f32>(); }
        ),
        projectionMatrixInverse(
            [] (M &mat) { mat = IdentityTransform<f32>(); }
        ),
        viewMatrixInverse(
            [] (M &mat) { mat = IdentityTransform<f32>(); }
        ),
        projectionViewMatrixInverse(
            [] (M &mat) { mat = IdentityTransform<f32>(); }
        ),
        depthRange(0.0, 1.0),
        clearDepth(1.0),
        clearStencil(0) {
    }

    Camera(const M &projectionMatrix, const M &viewMatrix) : _projectionMatrix(projectionMatrix), _viewMatrix(viewMatrix),
        projectionViewMatrix(
            [this] (M &mat) { mat = this->_projectionMatrix * this->_viewMatrix; }
        ),
        projectionMatrixInverse(
            [this] (M &mat) { mat = inverse(this->_projectionMatrix); }
        ),
        viewMatrixInverse(
            [this] (M &mat) { mat = inverse(this->_viewMatrix); }
        ),
        projectionViewMatrixInverse(
            [this] (M &mat) { mat = inverse(this->projectionViewMatrix()); }
        ),
        depthRange(0.0, 1.0),
        clearDepth(1.0),
        clearStencil(0) {
    }

    Camera(const Camera &camera) : _projectionMatrix(camera._projectionMatrix), _viewMatrix(camera._viewMatrix),
        projectionViewMatrix(
            [this] (M &mat) { mat = this->_projectionMatrix * this->_viewMatrix; }
        ),
        projectionMatrixInverse(
            [this] (M &mat) { mat = inverse(this->_projectionMatrix); }
        ),
        viewMatrixInverse(
            [this] (M &mat) { mat = inverse(this->_viewMatrix); }
        ),
        projectionViewMatrixInverse(
            [this] (M &mat) { mat = inverse(this->projectionViewMatrix()); }
        ),
        viewport(camera.viewport),
        depthRange(camera.depthRange),
        clearColor(camera.clearColor),
        clearDepth(camera.clearDepth),
        clearStencil(camera.clearStencil) {
    }


    Camera & operator =(const Camera &camera) {
        this->_projectionMatrix = camera._projectionMatrix;
        this->_viewMatrix = camera._viewMatrix;
        this->projectionViewMatrix = camera.projectionViewMatrix;
        this->projectionMatrixInverse = camera.projectionMatrixInverse;
        this->viewMatrixInverse = camera.viewMatrixInverse;
        this->projectionViewMatrixInverse = camera.projectionViewMatrixInverse;
        this->viewport = camera.viewport;
        this->depthRange = camera.depthRange;
        this->clearColor = camera.clearColor;
        this->clearDepth = camera.clearDepth;
        this->clearStencil = camera.clearStencil;
        return *this;
    }


    inline const M &projectionMatrix() const {
        return this->_projectionMatrix;
    }

    inline const M &viewMatrix() const {
        return this->_viewMatrix;
    }


    inline Camera withProjectionMatrix(const M &projectionMatrix) const {
        Camera copy(*this);

        copy._projectionMatrix = projectionMatrix;
        return copy;
    }

    inline Camera withViewMatrix(const M &viewMatrix) const {
        Camera copy(*this);

        copy._viewMatrix = viewMatrix;
        return copy;
    }


    Vector<f32, 3> unprojectPoint(const Vector<i32, 3> &window);

    Line<f32, 3> unprojectLine(const Vector<i32, 2> &window);
};


#endif //__CAMERA_H_INCLUDE__