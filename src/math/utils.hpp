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

#ifndef __MATH_UTILS_H_INCLUDE__
#define __MATH_UTILS_H_INCLUDE__


#define EPS_FLOAT        1.19e-07
#define EPS_DOUBLE       2.22e-16
#define EPS_LONG_DOUBLE  1.08e-19


#define _min(a, b)  ((a) < (b) ? (a) : (b))
#define _max(a, b)  ((a) > (b) ? (a) : (b))


template<typename T>
inline T _eps(const T &scale = T(1)) {
    return T(0);
}

template<>
inline float _eps<float>(const float &scale) {
    return EPS_FLOAT * scale;
}

template<>
inline double _eps<double>(const double &scale) {
    return EPS_DOUBLE * scale;
}

template<>
inline long double _eps<long double>(const long double &scale) {
    return EPS_LONG_DOUBLE * scale;
}


inline float _abs(float value) {
    return fabsf(value);
}

inline double _abs(double value) {
    return fabs(value);
}

inline long double _abs(long double value) {
    return fabsl(value);
}


inline float _copysign(float dst, float src) {
    return copysignf(dst, src);
}

inline double _copysign(double dst, double src) {
    return copysign(dst, src);
}

inline long double _copysign(long double dst, long double src) {
    return copysignl(dst, src);
}


inline float _sqrt(float value) {
    return sqrtf(value);
}

inline double _sqrt(double value) {
    return sqrt(value);
}

inline long double _sqrt(long double value) {
    return sqrtl(value);
}


inline float _hypot(float a, float b) {
    return hypotf(a, b);
}

inline double _hypot(double a, double b) {
    return hypot(a, b);
}

inline long double _hypot(long double a, long double b) {
    return hypotl(a, b);
}


inline float _sin(float value) {
    return sinf(value);
}

inline double _sin(double value) {
    return sin(value);
}

inline long double _sin(long double value) {
    return sinl(value);
}


inline float _asin(float value) {
    return asinf(value);
}

inline double _asin(double value) {
    return asin(value);
}

inline long double _asin(long double value) {
    return asinl(value);
}


inline float _cos(float value) {
    return cosf(value);
}

inline double _cos(double value) {
    return cos(value);
}

inline long double _cos(long double value) {
    return cosl(value);
}


inline float _acos(float value) {
    return acosf(value);
}

inline double _acos(double value) {
    return acos(value);
}

inline long double _acos(long double value) {
    return acosl(value);
}


inline float _tan(float value) {
    return tanf(value);
}

inline double _tan(double value) {
    return tan(value);
}

inline long double _tan(long double value) {
    return tanl(value);
}


inline float _atan(float value) {
    return atanf(value);
}

inline double _atan(double value) {
    return atan(value);
}

inline long double _atan(long double value) {
    return atanl(value);
}


inline float _atan2(float y, float x) {
    return atan2f(y, x);
}

inline double _atan2(double y, double x) {
    return atan2(y, x);
}

inline long double _atan2(long double y, long double x) {
    return atan2l(y, x);
}


template<typename T>
inline bool _eq(const T &a, const T &b) {
    return _abs(a - b) <= _eps<T>(T(100));
}

template<typename T>
inline bool _ne(const T &a, const T &b) {
    return !_eq(a, b);
}

template<typename T>
inline bool _eq0(const T &a) {
    return _eq(a, T(0));
}

template<typename T>
inline bool _eq1(const T &a) {
    return _eq(a, T(1));
}

template<typename T>
inline bool _ne0(const T &a) {
    return !_eq0(a);
}

template<typename T>
inline bool _ne1(const T &a) {
    return !_eq1(a);
}


#endif //__MATH_UTILS_H_INCLUDE__