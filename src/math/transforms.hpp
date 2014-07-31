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

#ifndef __MATH_TRANSFORMS_H_INCLUDE__
#define __MATH_TRANSFORMS_H_INCLUDE__


template<typename T>
inline Matrix<T, 4, 4> IdentityTransform() {
    return Matrix4x4<T>(
        T(1), T(0), T(0), T(0),
        T(0), T(1), T(0), T(0),
        T(0), T(0), T(1), T(0),
        T(0), T(0), T(0), T(1)
    );
}

template<typename T>
inline Matrix<T, 4, 4> TranslateTransform(const T &x, const T &y, const T &z) {
    return Matrix4x4<T>(
        T(1), T(0), T(0),    x,
        T(0), T(1), T(0),    y,
        T(0), T(0), T(1),    z,
        T(0), T(0), T(0), T(1)
    );
}

template<typename T>
inline Matrix<T, 4, 4> TranslateTransform(const Vector<T, 3> &vec) {
    return TranslateTransform(vec[0], vec[1], vec[2]);
}

template<typename T>
inline Matrix<T, 4, 4> ScaleTransform(const T &x, const T &y, const T &z) {
    return Matrix4x4<T>(
        x,    T(0), T(0), T(0),
        T(0),    y, T(0), T(0),
        T(0), T(0),    z, T(0),
        T(0), T(0), T(0), T(1)
    );
}

template<typename T>
inline Matrix<T, 4, 4> ScaleTransform(const Vector<T, 3> &vec) {
    return ScaleTransform(vec[0], vec[1], vec[2]);
}

template<typename T>
inline Matrix<T, 4, 4> RotateTransform(const T &angle, const T &x, const T &y, const T &z) {
    const Vector<T, 3> axis(normalize(Vector3<T>(x, y, z)));
    const T &nx(axis[0]);
    const T &ny(axis[1]);
    const T &nz(axis[2]);
    const T s(_sin(angle));
    const T c(_cos(angle));

    return Matrix4x4<T>(
        nx * nx * (T(1) - c) +      c,  nx * ny * (T(1) - c) - nz * s,  nx * nz * (T(1) - c) + ny * s,  T(0),
        nx * ny * (T(1) - c) + nz * s,  ny * ny * (T(1) - c) +      c,  ny * nz * (T(1) - c) - nx * s,  T(0),
        nx * nz * (T(1) - c) - ny * s,  ny * nz * (T(1) - c) + nx * s,  nz * nz * (T(1) - c) +      c,  T(0),
                                 T(0),                           T(0),                           T(0),  T(1)
    );
}

template<typename T>
inline Matrix<T, 4, 4> RotateTransform(const T &angle, const Vector<T, 3> &axis) {
    return RotateTransform(angle, axis[0], axis[1], axis[2]);
}

template<typename T>
inline Matrix<T, 4, 4> RotateXTransform(const T &angle) {
    return RotateTransform(angle, T(1), T(0), T(0));
}

template<typename T>
inline Matrix<T, 4, 4> RotateYTransform(const T &angle) {
    return RotateTransform(angle, T(0), T(1), T(0));
}

template<typename T>
inline Matrix<T, 4, 4> RotateZTransform(const T &angle) {
    return RotateTransform(angle, T(0), T(0), T(1));
}

template<typename T>
inline Matrix<T, 4, 4> LookAtTransform(const Vector<T, 3> &direction, const Vector<T, 3> &up) {
    const Vector<T, 3> f(normalize(direction));
    const Vector<T, 3> s(normalize(cross(f, normalize(up))));
    const Vector<T, 3> u(normalize(cross(s, f)));

    return Matrix4x4<T>(
        s[0],  u[0], -f[0],  T(0),
        s[1],  u[1], -f[1],  T(0),
        s[2],  u[2], -f[2],  T(0),
        T(0),  T(0),  T(0),  T(1)
    );
}

template<typename T>
inline Matrix<T, 4, 4> LookAtTransform(const Vector<T, 3> &eye, const Vector<T, 3> &center, const Vector<T, 3> &up) {
    return LookAtTransform(center - eye, up) * TranslateTransform(-eye);
}

template<typename T>
inline Matrix<T, 4, 4> LookAroundYTransform(const Vector<T, 3> &center, const T &radius, const T &theta, const T &phi) {
    return LookAtTransform(
        Vector3<T>(
            center[0] + radius * _cos(theta) * _cos(phi),
            center[1] + radius * _sin(phi),
            center[2] + radius * _sin(theta) * _cos(phi)
        ),
        center,
        Vector3<T>(T(0), T(1), T(0))
    );
}

template<typename T>
inline Matrix<T, 4, 4> OrthographicProjection(T left, T right, T bottom, T top, T znear, T zfar) {
    return Matrix4x4<T>(
                  T(2) / (right - left),                           T(0),                              T(0),       -(right + left) / (right - left),
                                   T(0),          T(2) / (top - bottom),                              T(0),       -(top + bottom) / (top - bottom),
                                   T(0),                           T(0),            -T(2) / (zfar - znear),       -(zfar + znear) / (zfar - znear),
                                   T(0),                           T(0),                              T(0),                                   T(1)
    );
}

template<typename T>
inline Matrix<T, 4, 4> OrthographicProjection(T width, T height) {
    return OrthographicProjection(T(0), width, height, T(0), -T(1), T(1));
}

template<typename T>
inline Matrix<T, 4, 4> PerspectiveProjection(T fovy, T aspect, T znear, T zfar) {
    const T f(T(1) / _tan(fovy));

    return Matrix4x4<T>(
                             f / aspect,                           T(0),                              T(0),                                   T(0),
                                   T(0),                              f,                              T(0),                                   T(0),
                                   T(0),                           T(0),  -(zfar + znear) / (znear - zfar),  -T(2) * zfar * znear / (znear - zfar),
                                   T(0),                           T(0),                             -T(1),                                   T(0)
    );
}

template<typename T>
inline Matrix<T, 4, 4> InfinitePerspectiveProjection(T fovy, T aspect, T znear) {
    const T f(T(1) / _tan(fovy));

    return Matrix4x4<T>(
                             f / aspect,                           T(0),                              T(0),                                   T(0),
                                   T(0),                              f,                              T(0),                                   T(0),
                                   T(0),                           T(0),                             -T(1),                          -T(2) * znear,
                                   T(0),                           T(0),                             -T(1),                                   T(0)
    );
}

template<typename T>
inline Matrix<T, 4, 4> FrustumProjection(T left, T right, T bottom, T top, T znear, T zfar) {
    return Matrix4x4<T>(
          T(2) * znear / (right - left),                           T(0),   (right + left) / (right - left),                                   T(0),
                                   T(0),  T(2) * znear / (top - bottom),   (top + bottom) / (top - bottom),                                   T(0),
                                   T(0),                           T(0),  -(zfar + znear) / (zfar - znear),  -T(2) * zfar * znear / (zfar - znear),
                                   T(0),                           T(0),                             -T(1),                                   T(0)
    );
}

template<typename T>
inline Matrix<T, 4, 4> InfiniteFrustumProjection(T left, T right, T bottom, T top, T znear) {
    return Matrix4x4<T>(
          T(2) * znear / (right - left),                           T(0),   (right + left) / (right - left),                                   T(0),
                                   T(0),  T(2) * znear / (top - bottom),   (top + bottom) / (top - bottom),                                   T(0),
                                   T(0),                           T(0),                             -T(1),                          -T(2) * znear,
                                   T(0),                           T(0),                             -T(1),                                   T(0)
    );
}


#endif //__MATH_TRANSFORMS_H_INCLUDE__