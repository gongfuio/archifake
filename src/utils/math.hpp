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
*/

#ifndef __MATH_H_INCLUDE__
#define __MATH_H_INCLUDE__


#include <math.h>
#include <stdlib.h>
#include <stdio.h>


#define EPS_FLOAT      1.19e-07
#define EPS_DOUBLE     2.22e-16


#define MIN(a, b)  ((a) < (b) ? (a) : (b))
#define MAX(a, b)  ((a) > (b) ? (a) : (b))


inline bool equals(float a, float b, float eps = EPS_FLOAT * 100) {
    return (fabsf(a - b) <= eps);
}

inline bool equals(double a, double b, double eps = EPS_DOUBLE * 100) {
    return (fabs(a - b) <= eps);
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
        for (int i = MIN(n, n2) - 1; i >= 0; i--) {
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
        for (int i = MIN(n, n2) - 1; i >= 0; i--) {
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
            if (!equals(this->data[i], vec[i])) {
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

        for (int i = n - 1; i >= 0; i--) {
            dst[i] = this->data[i] / scalar;
        }
        return dst;
    }

    Vector<T, n> & operator /= (T scalar) {
        for (int i = n - 1; i >= 0; i--) {
            this->data[i] /= scalar;
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
            dst[i] = this->data[i] >= T(0) ? this->data[i] : -this->data[i];
        }
        return dst;
    }

    Vector<T, n> & abs() {
        for (int i = n - 1; i >= 0; i--) {
            if (this->data[i] >= T(0)) {
                this->data[i] = -this->data[i];
            }
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


    bool null() const {
        for (int i = n - 1; i >= 0; i--) {
            if (!equals(this->data[i], T(0))) {
                return false;
            }
        }
        return true;
    }


    // operator Vector<T, 2>() const {
    //     if (n == 0) {
    //         return Vector<T, 2>();
    //     }
    //     if (n == 1) {
    //         return Vector<T, 2>(this->data[0]);
    //     }
    //     return Vector<T, 2>(this->data[0], this->data[1]);
    // }

    // operator Vector<T, 3>() const {
    //     if (n == 0) {
    //         return Vector<T, 3>();
    //     }
    //     if (n == 1) {
    //         return Vector<T, 3>(this->data[0]);
    //     }
    //     if (n == 2) {
    //         return Vector<T, 3>(this->data[0], this->data[1]);
    //     }
    //     return Vector<T, 3>(this->data[0], this->data[1], this->data[2]);
    // }

    // operator Vector<T, 4>() const {
    //     if (n == 0) {
    //         return Vector<T, 4>();
    //     }
    //     if (n == 1) {
    //         return Vector<T, 4>(this->data[0]);
    //     }
    //     if (n == 2) {
    //         return Vector<T, 4>(this->data[0], this->data[1]);
    //     }
    //     if (n == 3) {
    //         return Vector<T, 4>(this->data[0], this->data[1], this->data[2]);
    //     }
    //     return Vector<T, 4>(this->data[0], this->data[1], this->data[2], this->data[3]);
    // }


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


template<int n>
float norm(const Vector<float, n> &vec) {
    return sqrtf(vec.dot());
}

template<int n>
double norm(const Vector<double, n> &vec) {
    return sqrt(vec.dot());
}

template<int n>
long double norm(const Vector<long double, n> &vec) {
    return sqrtl(vec.dot());
}

template<typename T, int n>
Vector<T, n> normalize(const Vector<T, n> &vec) {
    T l = (T)norm(vec);

    if (!equals(l, T(0))) {
        return (vec * (T(1) / l));
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
        for (int i = MIN(m, m2) - 1; i >= 0; i--) {
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
        for (int i = MIN(m, m2) - 1; i >= 0; i--) {
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
            if (!equals(this->data[i], mat[i])) {
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

        for (int i = m - 1; i >= 0; i--) {
            dst[i] = this->data[i] / scalar;
        }
        return dst;
    }

    Matrix<T, m, n> & operator /= (T scalar) {
        for (int i = m - 1; i >= 0; i--) {
            this->data[i] /= scalar;
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


    bool null() const {
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (this->data[i][j] != T(0)) {
                    return false;
                }
            }
        }
        return true;
    }

    bool diagonal() const {
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (i != j && !equals(this->data[i][j], T(0))) {
                    return false;
                }
            }
        }
        return true;
    }

    bool identity() const {
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (i == j) {
                    if (!equals(this->data[i][j], T(1))) {
                        return false;
                    }
                } else if (!equals(this->data[i][j], T(0))) {
                    return false;
                }
            }
        }
        return true;
    }

    bool orthogonal() const {
        (*this * this->transpose()).print();
        return (*this * this->transpose()).identity();
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
    unsigned long flags[mat.bits];

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
    T dst = 0;

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
        T l = norm(dst[i]);

        if (!equals(l, T(0))) {
            dst[i] *= T(1) / l;
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
        T l = norm(q[i]);

        if (!equals(l, T(0))) {
            q[i] *= T(1) / l;
            r[i][i] = l;

            for (int k = i + 1; k < n; k++) {
                l = q[i].dot(q[k]);
                q[k] -= q[i] * l;
                r[i][k] = l;
            }
        } else {
            q[i].zeros();
        }
    }
    transpose(q);
}

template<typename T, int m, int n>
void svd(const Matrix<T, m, n> &mat, Matrix<T, m, m> &u, Matrix<T, m, n> &s, Matrix<T, n, n> &v) {
    // TODO:
}

template<typename T, int n>
Matrix<T, n, n> inverse(const Matrix<T, n, n> &mat) {
    Matrix<T, n, n> dst(cofactors(mat));
    T det = dst.row(0).dot(mat.row(0));

    if (det != T(0)) {
        transpose(dst);
        dst *= T(1) / det;
    } else {
        Matrix<T, n, n> u, s, v;

        svd(mat, u, s, v);
        for (int i = n - 1; i >= 0; i--) {
            if (!equals(s[i][i], T(0))) {
                s[i][i] = T(1) / s[i][i];
            } else {
                s[i][i] = T(0);
            }
        }
        dst = v * s * v.transpose();
    }
    return dst;
}


#endif //__MATH_H_INCLUDE__