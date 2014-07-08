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

#ifndef __MATH_H_INCLUDE__
#define __MATH_H_INCLUDE__


#include <math.h>
#include <stdlib.h>
#include <stdio.h>


#define EPS_FLOAT        1.19e-07
#define EPS_DOUBLE       2.22e-16
#define EPS_LONG_DOUBLE  1.08e-19


#define _min(a, b)  ((a) < (b) ? (a) : (b))
#define _max(a, b)  ((a) > (b) ? (a) : (b))


template<typename T>
inline T _eps(T scale = T(1)) {
    return T(0);
}

template<>
inline float _eps<float>(float scale) {
    return EPS_FLOAT * scale;
}

template<>
inline double _eps<double>(double scale) {
    return EPS_DOUBLE * scale;
}

template<>
inline long double _eps<long double>(long double scale) {
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


template<typename T>
inline bool _eq(T a, T b) {
    return _abs(a - b) <= _eps<T>(T(100));
}

template<typename T>
inline bool _ne(T a, T b) {
    return !_eq(a, b);
}

template<typename T>
inline bool _eq0(T a) {
    return _eq(a, T(0));
}

template<typename T>
inline bool _eq1(T a) {
    return _eq(a, T(1));
}

template<typename T>
inline bool _ne0(T a) {
    return !_eq0(a);
}

template<typename T>
inline bool _ne1(T a) {
    return !_eq1(a);
}


template<typename T, int n>
class Vector {
protected:
    T data[n];


public:
    const int size = n;
    const int cols = n;


    inline Vector() {
        for (int i = n - 1; i >= 0; i--) {
            this->data[i] = T(0);
        }
    }

    inline Vector(const T data[n]) {
        for (int i = n - 1; i >= 0; i--) {
            this->data[i] = data[i];
        }
    }

    inline Vector(const Vector<T, n> &vec) {
        for (int i = n - 1; i >= 0; i--) {
            this->data[i] = vec[i];
        }
    }

    template<int n2>
    Vector(const Vector<T, n2> &vec) {
        for (int i = _min(n, n2) - 1; i >= 0; i--) {
            this->data[i] = vec[i];
        }
        for (int i = n - 1; i >= n2; i--) {
            this->data[i] = T(0);
        }
    }


    Vector<T, n> & operator =(const Vector<T, n> &vec) {
        for (int i = n - 1; i >= 0; i--) {
            this->data[i] = vec[i];
        }
        return *this;
    }

    template<int n2>
    Vector<T, n> & operator =(const Vector<T, n2> &vec) {
        for (int i = _min(n, n2) - 1; i >= 0; i--) {
            this->data[i] = vec[i];
        }
        for (int i = n - 1; i >= n2; i--) {
            this->data[i] = T(0);
        }
        return *this;
    }


    inline T & operator [] (int i) {
        return this->data[i];
    }

    inline const T & operator [] (int i) const {
        return this->data[i];
    }


    int operator ==(const Vector<T, n> &vec) const {
        for (int i = n - 1; i >= 0; i--) {
            if (!_eq(this->data[i], vec[i])) {
                return false;
            }
        }
        return true;
    }

    inline int operator !=(const Vector<T, n> &vec) const {
        return !(*this == vec);
    }


    inline int operator <(const Vector<T, n> &vec) const {
        return this->dot() < vec.dot();
    }

    inline int operator <=(const Vector<T, n> &vec) const {
        return this->dot() <= vec.dot();
    }

    inline int operator >(const Vector<T, n> &vec) const {
        return this->dot() > vec.dot();
    }

    inline int operator >=(const Vector<T, n> &vec) const {
        return this->dot() >= vec.dot();
    }


    Vector<T, n> operator -() const {
        Vector<T, n> dst;

        for (int i = n - 1; i >= 0; i--) {
            dst[i] = -this->data[i];
        }
        return dst;
    }

    Vector<T, n> operator * (T scalar) const {
        Vector<T, n> dst;

        for (int i = n - 1; i >= 0; i--) {
            dst[i] = this->data[i] * scalar;
        }
        return dst;
    }

    Vector<T, n> & operator *= (T scalar) {
        for (int i = n - 1; i >= 0; i--) {
            this->data[i] *= scalar;
        }
        return *this;
    }

    Vector<T, n> operator / (T scalar) const {
        Vector<T, n> dst;

        scalar = T(1) / scalar;
        for (int i = n - 1; i >= 0; i--) {
            dst[i] = this->data[i] * scalar;
        }
        return dst;
    }

    Vector<T, n> & operator /= (T scalar) {
        scalar = T(1) / scalar;
        for (int i = n - 1; i >= 0; i--) {
            this->data[i] *= scalar;
        }
        return *this;
    }


    Vector<T, n> operator + (const Vector<T, n> &vec) const {
        Vector<T, n> dst;

        for (int i = n - 1; i >= 0; i--) {
            dst[i] = this->data[i] + vec[i];
        }
        return dst;
    }

    Vector<T, n> & operator += (const Vector<T, n> &vec) {
        for (int i = n - 1; i >= 0; i--) {
            this->data[i] += vec[i];
        }
        return *this;
    }

    Vector<T, n> operator - (const Vector<T, n> &vec) const {
        Vector<T, n> dst;

        for (int i = n - 1; i >= 0; i--) {
            dst[i] = this->data[i] - vec[i];
        }
        return dst;
    }

    Vector<T, n> & operator -= (const Vector<T, n> &vec) {
        for (int i = n - 1; i >= 0; i--) {
            this->data[i] -= vec[i];
        }
        return *this;
    }

    Vector<T, n> operator * (const Vector<T, n> &vec) const {
        Vector<T, n> dst;

        for (int i = n - 1; i >= 0; i--) {
            dst[i] = this->data[i] * vec[i];
        }
        return dst;
    }

    Vector<T, n> & operator *= (const Vector<T, n> &vec) {
        for (int i = n - 1; i >= 0; i--) {
            this->data[i] *= vec[i];
        }
        return *this;
    }

    Vector<T, n> operator / (const Vector<T, n> &vec) const {
        Vector<T, n> dst;

        for (int i = n - 1; i >= 0; i--) {
            dst[i] = this->data[i] / vec[i];
        }
        return dst;
    }

    Vector<T, n> & operator /= (const Vector<T, n> &vec) {
        for (int i = n - 1; i >= 0; i--) {
            this->data[i] /= vec[i];
        }
        return *this;
    }


    void fill(T value) {
        for (int i = n - 1; i >= 0; i--) {
            this->data[i] = value;
        }
    }

    inline void zeros() {
        this->fill(T(0));
    }

    inline void ones() {
        this->fill(T(1));
    }


    Vector<T, n> abs() const {
        Vector<T, n> dst;

        for (int i = n - 1; i >= 0; i--) {
            dst[i] = (T)_abs(this->data[i]);
        }
        return dst;
    }

    Vector<T, n> & abs() {
        for (int i = n - 1; i >= 0; i--) {
            this->data[i] = (T)_abs(this->data[i]);
        }
        return *this;
    }


    T dot(const Vector<T, n> &vec) const {
        T value = 0;

        for (int i = n - 1; i >= 0; i--) {
            value += this->data[i] * vec[i];
        }
        return value;
    }

    inline T dot() const {
        return this->dot(*this);
    }


    bool isNull() const {
        for (int i = n - 1; i >= 0; i--) {
            if (_ne0(this->data[i])) {
                return false;
            }
        }
        return true;
    }


    void print(const char *name) const {
        printf("%s[%d]=\n", name, n);
        this->print();
        printf("\n");
    }

    void print() const {
        for (int i = 0; i < n; i++) {
            if (i > 0) {
                printf(" ");
            }
            printf("%.05f", (double)this->data[i]);
        }
        printf("\n");
    }
};


template<typename T>
inline Vector<T, 2> Vector2(T x, T y) {
    T data[2] = { x, y };

    return Vector<T, 2>(data);
}

template<typename T>
inline Vector<T, 3> Vector3(T x, T y, T z) {
    T data[3] = { x, y, z };

    return Vector<T, 3>(data);
}

template<typename T>
inline Vector<T, 4> Vector4(T x, T y, T z, T w) {
    T data[4] = { x, y, z, w };

    return Vector<T, 4>(data);
}


template<typename T, int n>
inline T norm(const Vector<T, n> &vec) {
    return _sqrt(vec.dot());
}

template<typename T, int n>
Vector<T, n> normalize(const Vector<T, n> &vec) {
    T length = (T)norm(vec);

    if (_ne0(length)) {
        return vec / length;
    }
    return Vector<T, n>();
}



template<typename T, int m, int n>
class Matrix {
protected:
    Vector<T, n> data[m];


public:
    const int size = m * n;
    const int bits = ((size % 8) == 0 ? (size >> 3) : ((size + (8 - size % 8)) >> 3));
    const int rows = m;
    const int cols = n;


    inline Matrix() {
    }

    inline Matrix(const T data[m][n]) {
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                this->data[i][j] = data[i][j];
            }
        }
    }

    inline Matrix(const Vector<T, n> data[m]) {
        for (int i = m - 1; i >= 0; i--) {
            this->data[i] = data[i];
        }
    }

    inline Matrix(const Matrix<T, m, n> &mat) {
        for (int i = m - 1; i >= 0; i--) {
            this->data[i] = mat[i];
        }
    }

    template<int m2, int n2>
    Matrix(const Matrix<T, m2, n2> &mat) {
        for (int i = _min(m, m2) - 1; i >= 0; i--) {
            this->data[i] = mat[i];
        }
    }


    Matrix<T, m, n> & operator =(const Matrix<T, m, n> &mat) {
        for (int i = m - 1; i >= 0; i--) {
            this->data[i] = mat[i];
        }
        return *this;
    }

    template<int m2, int n2>
    Matrix<T, m, n> & operator =(const Matrix<T, m2, n2> &mat) {
        for (int i = _min(m, m2) - 1; i >= 0; i--) {
            this->data[i] = mat[i];
        }
        for (int i = m - 1; i >= m2; i--) {
            this->data[i].zeros();
        }
        return *this;
    }


    inline Vector<T, n> & operator [] (int i) {
        return this->data[i];
    }

    inline const Vector<T, n> & operator [] (int i) const {
        return this->data[i];
    }


    inline const Vector<T, n> & row(int i) const {
        return this->data[i];
    }

    inline void row(int i, const Vector<T, n> &v) {
        this->data[i] = v;
    }

    inline const Vector<T, m> col(int j) const {
        Vector<T, m> dst;

        for (int i = m - 1; i >= 0; i--) {
            dst[i] = this->data[i][j];
        }
        return dst;
    }

    inline void col(int j, const Vector<T, m> &v) {
        for (int i = m - 1; i >= 0; i--) {
            this->data[i][j] = v[i];
        }
    }


    inline T & operator () (int i, int j) {
        return this->data[i][j];
    }

    inline const T & operator () (int i, int j) const {
        return this->data[i][j];
    }


    int operator ==(const Matrix<T, m, n> &mat) const {
        for (int i = m - 1; i >= 0; i--) {
            if (_ne(this->data[i], mat[i])) {
                return false;
            }
        }
        return true;
    }

    inline int operator !=(const Matrix<T, m, n> &mat) const {
        return !(*this == mat);
    }


    Matrix<T, m, n> operator -() const {
        Matrix<T, m, n> dst;

        for (int i = m - 1; i >= 0; i--) {
            dst[i] = -this->data[i];
        }
        return dst;
    }

    Matrix<T, m, n> operator * (T scalar) const {
        Matrix<T, m, n> dst;

        for (int i = m - 1; i >= 0; i--) {
            dst[i] = this->data[i] * scalar;
        }
        return dst;
    }

    Matrix<T, m, n> & operator *= (T scalar) {
        for (int i = m - 1; i >= 0; i--) {
            this->data[i] *= scalar;
        }
        return *this;
    }

    Matrix<T, m, n> operator / (T scalar) const {
        Matrix<T, m, n> dst;

        scalar = T(1) / scalar;
        for (int i = m - 1; i >= 0; i--) {
            dst[i] = this->data[i] * scalar;
        }
        return dst;
    }

    Matrix<T, m, n> & operator /= (T scalar) {
        scalar = T(1) / scalar;
        for (int i = m - 1; i >= 0; i--) {
            this->data[i] *= scalar;
        }
        return *this;
    }


    Matrix<T, m, n> operator + (const Matrix<T, m, n> &mat) const {
        Matrix<T, m, n> dst;

        for (int i = m - 1; i >= 0; i--) {
            dst[i] = this->data[i] + mat[i];
        }
        return dst;
    }

    Matrix<T, m, n> & operator += (const Matrix<T, m, n> &mat) {
        for (int i = m - 1; i >= 0; i--) {
            this->data[i] += mat[i];
        }
        return *this;
    }

    Matrix<T, m, n> operator - (const Matrix<T, m, n> &mat) const {
        Matrix<T, m, n> dst;

        for (int i = m - 1; i >= 0; i--) {
            dst[i] = this->data[i] - mat[i];
        }
        return dst;
    }

    Matrix<T, m, n> & operator -= (const Matrix<T, m, n> &mat) {
        for (int i = m - 1; i >= 0; i--) {
            this->data[i] -= mat[i];
        }
        return *this;
    }

    Vector<T, m> operator * (const Vector<T, m> &v) const {
        Vector<T, n> dst;

        for (int i = m - 1; i >= 0; i--) {
            dst[i] = this->row(i).dot(v);
        }
        return dst;
    }

    template<int p>
    Matrix<T, m, p> operator * (const Matrix<T, n, p> &mat) const {
        Matrix<T, m, p> dst;

        for (int i = m - 1; i >= 0; i--) {
            for (int j = p - 1; j >= 0; j--) {
                dst[i][j] = this->row(i).dot(mat.col(j));
            }
        }
        return dst;
    }


    void fill(T value) {
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                this->data[i][j] = value;
            }
        }
    }

    inline void zeros() {
        this->fill(T(0));
    }

    inline void ones() {
        this->fill(T(1));
    }

    void identity() {
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (i == j) {
                    this->data[i][j] = T(1);
                } else {
                    this->data[i][j] = T(0);
                }
            }
        }
    }


    Matrix<T, m, n> abs() const {
        Matrix<T, m, n> dst;

        for (int i = m - 1; i >= 0; i--) {
            dst[i] = this->data[i].abs();
        }
        return dst;
    }

    Matrix<T, m, n> & abs() {
        for (int i = m - 1; i >= 0; i--) {
            this->data[i] = this->data[i].abs();
        }
        return *this;
    }


    Matrix<T, n, m> transpose() const {
        Matrix<T, n, m> dst;

        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                dst[j][i] = this->data[i][j];
            }
        }
        return dst;
    }


    Matrix<T, n - 1, m - 1> exclude(int ei, int ej) const {
        Matrix<T, n - 1, m - 1> dst;
        int ti = n - 2, tj;

        for (int i = m - 1; i >= 0; i--) {
            if (i != ei) {
                tj = n - 2;
                for (int j = n - 1; j >= 0; j--) {
                    if (j != ej) {
                        dst[ti][tj] = this->data[i][j];
                        tj--;
                    }
                }
                ti--;
            }
        }
        return dst;
    };


    bool isNull() const {
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (_ne0(this->data[i][j])) {
                    return false;
                }
            }
        }
        return true;
    }

    bool isDiagonal() const {
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (i != j && _ne0(this->data[i][j])) {
                    return false;
                }
            }
        }
        return true;
    }

    bool isIdentity() const {
        if (!this->isDiagonal()) {
            return false;
        }
        for (int i = _min(m, n) - 1; i >= 0; i--) {
            if (_ne1(this->data[i][i])) {
                return false;
            }
        }
        return true;
    }

    inline bool isOrthogonal() const {
        return (*this * this->transpose()).isIdentity();
    }


    void print(const char *name) const {
        printf("%s[%dx%d]=\n", name, m, n);
        this->print();
        printf("\n");
    }

    void print() const {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (j > 0) {
                    printf(" ");
                }
                printf("%.05f", this->data[i][j]);
            }
            printf("\n");
        }
    }
};


template<typename T>
inline Matrix<T, 2, 2> Matrix2x2(T m11, T m12, T m21, T m22) {
    T data[2][2] = {
        { m11, m12 },
        { m21, m22 }
    };

    return Matrix<T, 2, 2>(data);
}

template<typename T>
inline Matrix<T, 3, 3> Matrix3x3(T m11, T m12, T m13, T m21, T m22, T m23, T m31, T m32, T m33) {
    T data[3][3] = {
        { m11, m12, m13 },
        { m21, m22, m23 },
        { m31, m32, m33 }
    };

    return Matrix<T, 3, 3>(data);
}

template<typename T>
inline Matrix<T, 4, 4> Matrix4x4(T m11, T m12, T m13, T m14, T m21, T m22, T m23, T m24, T m31, T m32, T m33, T m34, T m41, T m42, T m43, T m44) {
    T data[4][4] = {
        { m11, m12, m13, m14 },
        { m21, m22, m23, m24 },
        { m31, m32, m33, m34 },
        { m41, m42, m43, m44 }
    };

    return Matrix<T, 4, 4>(data);
}


template<typename T, int n>
void transpose(Matrix<T, n, n> &mat) {
    unsigned char flags[mat.bits];

    for (int i = mat.bits - 1; i >= 0; i--) {
        flags[i] = 0;
    }
    for (int i = n - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            if (i != j) {
                int bit1 = i * n + j;
                int bit2 = j * n + i;
                int bucket1 = (bit1 - bit1 % 8) >> 3;
                int bucket2 = (bit2 - bit2 % 8) >> 3;

                if (((flags[bucket1] & 1 << (bit1 % 8)) | (flags[bucket2] & 1 << (bit2 % 8))) == 0) {
                    T tmp = mat[i][j];

                    mat[i][j] = mat[j][i];
                    mat[j][i] = tmp;

                    flags[bucket1] |= 1 << (bit1 % 8);
                    flags[bucket2] |= 1 << (bit2 % 8);
                }
            }
        }
    }
}

template<typename T, int n>
T trace(const Matrix<T, n, n> &mat) {
    T dst = T(0);

    for (int i = n - 1; i >= 0; i--) {
        dst += mat[i][i];
    }
    return dst;
}

template<typename T, int n>
Matrix<T, n, n> cofactors(const Matrix<T, n, n> &mat) {
    T data[n][n];

    for (int i = n - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            if (((i + j) % 2) == 0) {
                data[i][j] = determinant(mat.exclude(i, j));
            } else {
                data[i][j] = -determinant(mat.exclude(i, j));
            }
        }
    }
    return Matrix<T, n, n>(data);
}

template<typename T>
T determinant(const Matrix<T, 2, 2> &mat) {
    return (mat[0][0] * mat[1][1] - mat[1][0] * mat[0][1]);
}

template<typename T, int n>
T determinant(const Matrix<T, n, n> &mat) {
    return cofactors(mat).row(0).dot(mat.row(0));
}

template<typename T, int m, int n>
Matrix<T, m, n> orthonormalize(const Matrix<T, m, n> &mat) {
    Matrix<T, m, n> dst(mat);

    for (int i = 0; i < m; i++) {
        T length = norm(dst[i]);

        if (_ne0(length)) {
            dst[i] /= length;
            for (int k = i + 1; k < m; k++) {
                dst[k] -= dst[i] * dst[i].dot(dst[k]);
            }
        } else {
            dst[i].zeros();
        }
    }
    return dst;
}

template<typename T, int n>
void qr(const Matrix<T, n, n> &mat, Matrix<T, n, n> &q, Matrix<T, n, n> &r) {
    q = mat.transpose();
    r.zeros();
    for (int i = 0; i < n; i++) {
        T length = norm(q[i]);

        if (_ne0(length)) {
            q[i] /= length;
            r[i][i] = length;

            for (int k = i + 1; k < n; k++) {
                length = q[i].dot(q[k]);
                q[k] -= q[i] * length;
                r[i][k] = length;
            }
        } else {
            q[i].zeros();
        }
    }
    transpose(q);
}

template<typename T, int n>
void svd(const Matrix<T, n, n> &mat, Matrix<T, n, n> &u, Matrix<T, n, n> &s, Matrix<T, n, n> &v) {
    const int sweepmax = _max(12, 5 * n);
    const T tolerance = _eps<T>(T(10 * n));
    int count = 1;
    int sweep = 0;

    u = mat;
    s.zeros();
    for (int i = 0; i < n; i++) {
        s[i][i] = _eps<T>(norm(u.col(i)));
    }
    v.identity();
    while (count > 0 && sweep <= sweepmax) {
        count = n * (n - 1) / 2;
        for (int j = 0; j < n - 1; j++) {
            for (int k = j + 1; k < n; k++) {
                const Vector<T, n> &cj(u.col(j));
                const Vector<T, n> &ck(u.col(k));
                T ej = s[j][j];
                T ek = s[k][k];
                T aj = norm(cj);
                T ak = norm(ck);
                T alpha = T(2) * cj.dot(ck);

                if (aj >= ak && (_abs(alpha) <= (tolerance * aj * ak) || aj < ej || ak < ek)) {
                    count--;
                    continue;
                }

                T beta = aj * aj - ak * ak;
                T gamma = _hypot(alpha, beta);
                T cosine = T(0);
                T sine = T(1);

                if (_ne0(gamma)) {
                    if (beta > 0) {
                        cosine = _sqrt((beta + gamma) / (T(2) * gamma));
                        sine = alpha / (T(2) * gamma * cosine);
                    } else {
                        sine = _sqrt((gamma - beta) / (T(2) * gamma));
                        cosine = alpha / (T(2) * gamma * sine);
                    }
                }

                for (int i = 0; i < n; i++) {
                    T x = u[i][j];
                    T y = u[i][k];

                    u[i][j] =  x * cosine + y * sine;
                    u[i][k] = -x * sine   + y * cosine;
                }
                s[j][j] = _abs(cosine) * ej + _abs(sine)   * ek;
                s[k][k] = _abs(sine)   * ej + _abs(cosine) * ek;
                for (int i = 0; i < n; i++) {
                    T x = v[i][j];
                    T y = v[i][k];

                    v[i][j] =  x * cosine + y * sine;
                    v[i][k] = -x * sine   + y * cosine;
                }
            }
        }
        sweep++;
    }

    double plength = T(-1);

    for (int i = 0; i < n; i++) {
        Vector<T, n> uc(u.col(i));
        T length = norm(uc);

        if (length == T(0) || plength == T(0) || (i > 0 && length <= tolerance * plength)) {
            s[i][i] = 0;
            uc.zeros();
            plength = T(0);
        } else {
            s[i][i] = length;
            uc /= length;
            plength = length;
        }
        u.col(i, uc);
    }
}

template<typename T, int n>
Matrix<T, n, n> inverse(const Matrix<T, n, n> &mat) {
    Matrix<T, n, n> dst(cofactors(mat));
    T det = dst.row(0).dot(mat.row(0));

    if (!_eq(det, T(0))) {
        transpose(dst);
        dst *= T(1) / det;
    } else {
        Matrix<T, n, n> u, s, v;

        svd(mat, u, s, v);
        for (int i = n - 1; i >= 0; i--) {
            if (_ne0(s[i][i])) {
                s[i][i] = T(1) / s[i][i];
            } else {
                s[i][i] = T(0);
            }
        }
        transpose(v);
        dst = u * s * v;
    }
    return dst;
}


#endif //__MATH_H_INCLUDE__