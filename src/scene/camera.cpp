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


Vector<f32, 3> Camera::unprojectPoint(const Vector<i32, 3> &window) {
    auto vec = this->projectionViewMatrixInverse() * Vector4<f32>(
        (f32)(2 * (window[0] - this->viewport.x())) / (f32)this->viewport.width() - 1,
        (f32)(2 * (window[1] - this->viewport.y())) / (f32)this->viewport.height() - 1,
        (f32)(2 * window[3]) - 1,
        1
    );

    return Vector3<f32>(vec[0], vec[1], vec[2]);
}

Line<f32, 3> Camera::unprojectLine(const Vector<i32, 2> &window) {
    auto vec1 = this->projectionViewMatrixInverse() * Vector4<f32>(
        (f32)(2 * (window[0] - this->viewport.x())) / (f32)this->viewport.width() - 1,
        (f32)(2 * (window[1] - this->viewport.y())) / (f32)this->viewport.height() - 1,
        -1,
        1
    );
    auto vec2 = this->projectionViewMatrixInverse() * Vector4<f32>(
        (f32)(2 * (window[0] - this->viewport.x())) / (f32)this->viewport.width() - 1,
        (f32)(2 * (window[1] - this->viewport.y())) / (f32)this->viewport.height() - 1,
        1,
        1
    );

    return Line<f32, 3>(
        Vector3<f32>(vec1[0], vec1[1], vec1[2]),
        normalize(Vector3<f32>(vec2[0] - vec1[0], vec2[1] - vec1[1], vec2[2] - vec1[2]))
    );
}
