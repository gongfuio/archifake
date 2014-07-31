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
    Rectangle2<i32> _viewport;
    Range<f64> _depthRange;
    M _projectionMatrix;
    M _viewMatrix;

    LazyInitialized<M> _projectionViewMatrix;
    LazyInitialized<M> _projectionMatrixInverse;
    LazyInitialized<M> _viewMatrixInverse;
    LazyInitialized<M> _projectionViewMatrixInverse;


public:
    inline Camera() : _depthRange(0.0, 1.0), _projectionMatrix(IdentityTransform<f32>()), _viewMatrix(IdentityTransform<f32>()),
        _projectionViewMatrix(
            [] (M &mat) { mat = IdentityTransform<f32>(); }
        ),
        _projectionMatrixInverse(
            [] (M &mat) { mat = IdentityTransform<f32>(); }
        ),
        _viewMatrixInverse(
            [] (M &mat) { mat = IdentityTransform<f32>(); }
        ),
        _projectionViewMatrixInverse(
            [] (M &mat) { mat = IdentityTransform<f32>(); }
        )
    {
    }

    inline Camera(const Rectangle2<i32> &viewport, const Range<f64> &depthRange, const M &projectionMatrix, const M &viewMatrix) : _viewport(viewport), _depthRange(depthRange), _projectionMatrix(projectionMatrix), _viewMatrix(viewMatrix),
        _projectionViewMatrix(
            [this] (M &mat) { mat = this->_projectionMatrix * this->_viewMatrix; }
        ),
        _projectionMatrixInverse(
            [this] (M &mat) { mat = inverse(this->_projectionMatrix); }
        ),
        _viewMatrixInverse(
            [this] (M &mat) { mat = inverse(this->_viewMatrix); }
        ),
        _projectionViewMatrixInverse(
            [this] (M &mat) { mat = inverse(*this->_projectionViewMatrix); }
        )
    {
    }

    inline Camera(const Camera &camera) : _viewport(camera._viewport), _depthRange(camera._depthRange), _projectionMatrix(camera._projectionMatrix), _viewMatrix(camera._viewMatrix), _projectionViewMatrix(camera._projectionViewMatrix), _projectionMatrixInverse(camera._projectionViewMatrixInverse), _viewMatrixInverse(camera._viewMatrixInverse), _projectionViewMatrixInverse(camera._projectionViewMatrixInverse) {
    }


    Camera & operator =(const Camera &camera) {
        this->_viewport = camera._viewport;
        this->_depthRange = camera._depthRange;
        this->_projectionMatrix = camera._projectionMatrix;
        this->_viewMatrix = camera._viewMatrix;
        this->_projectionViewMatrix = camera._projectionViewMatrix;
        this->_projectionMatrixInverse = camera._projectionMatrixInverse;
        this->_viewMatrixInverse = camera._viewMatrixInverse;
        this->_projectionViewMatrixInverse = camera._projectionViewMatrixInverse;
        return *this;
    }


    inline const Rectangle2<i32> &viewport() const {
        return this->_viewport;
    }

    inline const Range<f64> &depthRange() const {
        return this->_depthRange;
    }

    inline const M &projectionMatrix() const {
        return this->_projectionMatrix;
    }

    inline const M &viewMatrix() const {
        return this->_viewMatrix;
    }


    inline const M & projectionViewMatrix() {
        return *this->_projectionViewMatrix;
    }

    inline const M & projectionMatrixInverse() {
        return *this->_projectionMatrixInverse;
    }

    inline const M & viewMatrixInverse() {
        return *this->_viewMatrixInverse;
    }

    inline const M & projectionViewMatrixInverse() {
        return *this->_projectionViewMatrixInverse;
    }


    inline Camera withViewport(const Rectangle2<i32> &viewport) const {
        return Camera(viewport, this->_depthRange, this->_projectionMatrix, this->_viewMatrix);
    }

    inline Camera withViewportAndProjection(const Rectangle2<i32> &viewport, const M &projectionMatrix) const {
        return Camera(viewport, this->_depthRange, projectionMatrix, this->_viewMatrix);
    }

    inline Camera withDepthRange(const Range<f64> &depthRange) const {
        return Camera(this->_viewport, depthRange, this->_projectionMatrix, this->_viewMatrix);
    }

    inline Camera withProjectionMatrix(const M &projectionMatrix) const {
        return Camera(this->_viewport, this->_depthRange, projectionMatrix, this->_viewMatrix);
    }

    inline Camera withViewMatrix(const M &viewMatrix) const {
        return Camera(this->_viewport, this->_depthRange, this->_projectionMatrix, viewMatrix);
    }


    Vector<f32, 3> unprojectPoint(const Vector<i32, 3> &window);

    Line<f32, 3> unprojectLine(const Vector<i32, 2> &window);
};


#endif //__CAMERA_H_INCLUDE__