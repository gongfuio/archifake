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
    Rectangle2<i32> viewport;
    Range<f64> depthRange;
    Matrix<f64, 4, 4> projectionMatrix;
    Matrix<f64, 4, 4> viewMatrix;


    Camera() {
    }
};


#endif //__CAMERA_H_INCLUDE__