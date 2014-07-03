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


template<typename T, i32u n>
class Vector {
protected:
    T data[n];


public:
    inline Vector() {
        memset(this->data, 0, sizeof(T) * n);
    }

    inline Vector(i32u size, const T *data) {
        memcpy(this->data, data, sizeof(T) * MIN(n, size));
    }

    inline Vector(const Vector<T, n> &ref) {
        memcpy(this->data, ref, sizeof(T) * n);
    }

    template<int m>
    inline Vector(const Vector<T, m> &ref) {
        memcpy(this->data, ref, sizeof(T) * MIN(n, m));
        if (n > m) {
            memset(this->data + m, 0, sizeof(T) * (n - m));
        }
    }

    Vector(T data0) {
        if (n == 0) {
            return;
        }
        this->data[0] = data0;
        if (n == 1) {
            return;
        }
        memset(this->data + 1, 0, sizeof(T) * (n - 1));
    }

    Vector(T data0, T data1) {
        if (n == 0) {
            return;
        }
        this->data[0] = data0;
        if (n == 1) {
            return;
        }
        this->data[1] = data1;
        if (n == 2) {
            return;
        }
        memset(this->data + 2, 0, sizeof(T) * (n - 2));
    }

    Vector(T data0, T data1, T data2) {
        if (n == 0) {
            return;
        }
        this->data[0] = data0;
        if (n == 1) {
            return;
        }
        this->data[1] = data1;
        if (n == 2) {
            return;
        }
        this->data[2] = data2;
        if (n == 3) {
            return;
        }
        memset(this->data + 3, 0, sizeof(T) * (n - 3));
    }

    Vector(T data0, T data1, T data2, T data3) {
        if (n == 0) {
            return;
        }
        this->data[0] = data0;
        if (n == 1) {
            return;
        }
        this->data[1] = data1;
        if (n == 2) {
            return;
        }
        this->data[2] = data2;
        if (n == 3) {
            return;
        }
        this->data[3] = data3;
        if (n == 4) {
            return;
        }
        memset(this->data + 4, 0, sizeof(T) * (n - 4));
    }


    inline i32u size() const {
        return n;
    }


    inline T & operator [] (int i) {
        return this->data[i];
    }

    inline const T & operator [] (int i) const {
        return this->data[i];
    }

    inline operator const T*() const {
        return this->data;
    }

    inline operator T*() const {
        return this->data;
    }


    operator T() const {
        if (n == 0) {
            return 0;
        }
        return this->data[0];
    }

    operator Vector<T, 2>() const {
        if (n == 0) {
            return Vector<T, 2>();
        }
        if (n == 1) {
            return Vector<T, 2>(this->data[0]);
        }
        return Vector<T, 2>(this->data[0], this->data[1]);
    }

    operator Vector<T, 3>() const {
        if (n == 0) {
            return Vector<T, 3>();
        }
        if (n == 1) {
            return Vector<T, 3>(this->data[0]);
        }
        if (n == 2) {
            return Vector<T, 3>(this->data[0], this->data[1]);
        }
        return Vector<T, 3>(this->data[0], this->data[1], this->data[2]);
    }

    operator Vector<T, 4>() const {
        if (n == 0) {
            return Vector<T, 4>();
        }
        if (n == 1) {
            return Vector<T, 4>(this->data[0]);
        }
        if (n == 2) {
            return Vector<T, 4>(this->data[0], this->data[1]);
        }
        if (n == 3) {
            return Vector<T, 4>(this->data[0], this->data[1], this->data[2]);
        }
        return Vector<T, 4>(this->data[0], this->data[1], this->data[2], this->data[3]);
    }


    Vector<T, n> operator -() const {
        Vector<T, n> dst;

        for (i32u i = 0; i < n; i++) {
            dst[i] = -this->data[i];
        }
        return dst;
    }

    Vector<T, n> operator * (T scalar) {
        Vector<T, n> dst;

        for (i32u i = 0; i < n; i++) {
            dst[i] = this->data[i] * scalar;
        }
        return dst;
    }

    Vector<T, n> & operator *= (T scalar) {
        for (i32u i = 0; i < n; i++) {
            this->data[i] *= scalar;
        }
        return *this;
    }

    Vector<T, n> operator / (T scalar) {
        Vector<T, n> dst;

        for (i32u i = 0; i < n; i++) {
            dst[i] = this->data[i] / scalar;
        }
        return dst;
    }

    Vector<T, n> & operator /= (T scalar) {
        for (i32u i = 0; i < n; i++) {
            this->data[i] /= scalar;
        }
        return *this;
    }


    Vector<T, n> operator + (const Vector<T, n> &v) {
        Vector<T, n> dst;

        for (i32u i = 0; i < n; i++) {
            dst[i] = this->data[i] + v[i];
        }
        return dst;
    }

    Vector<T, n> & operator += (const Vector<T, n> &v) {
        for (i32u i = 0; i < n; i++) {
            this->data[i] += v[i];
        }
        return *this;
    }

    Vector<T, n> operator - (const Vector<T, n> &v) {
        Vector<T, n> dst;

        for (i32u i = 0; i < n; i++) {
            dst[i] = this->data[i] + v[i];
        }
        return dst;
    }

    Vector<T, n> & operator -= (const Vector<T, n> &v) {
        for (i32u i = 0; i < n; i++) {
            this->data[i] += v[i];
        }
        return *this;
    }

    Vector<T, n> operator * (const Vector<T, n> &v) {
        Vector<T, n> dst;

        for (i32u i = 0; i < n; i++) {
            dst[i] = this->data[i] * v[i];
        }
        return dst;
    }

    Vector<T, n> & operator *= (const Vector<T, n> &v) {
        for (i32u i = 0; i < n; i++) {
            this->data[i] *= v[i];
        }
        return *this;
    }

    Vector<T, n> operator / (const Vector<T, n> &v) {
        Vector<T, n> dst;

        for (i32u i = 0; i < n; i++) {
            dst[i] = this->data[i] / v[i];
        }
        return dst;
    }

    Vector<T, n> & operator /= (const Vector<T, n> &v) {
        for (i32u i = 0; i < n; i++) {
            this->data[i] /= v[i];
        }
        return *this;
    }


    int operator ==(const Vector<T, n> &v) const {
        for (i32u i = 0; i < n; i++) {
            if (this->data[i] != v[i]) {
                return false;
            }
        }
        return true;
    }

    inline int operator !=(const Vector<T, n> &v) const {
        return !(*this == v);
    }


    inline int operator <(const Vector<T, n> &v) const {
        return this->dot() < v.dot();
    }

    inline int operator <=(const Vector<T, n> &v) const {
        return this->dot() <= v.dot();
    }

    inline int operator >(const Vector<T, n> &v) const {
        return this->dot() > v.dot();
    }

    inline int operator >=(const Vector<T, n> &v) const {
        return this->dot() >= v.dot();
    }


    T dot(const Vector<T, n> &v) const {
        T value = 0;

        for (i32u i = 0; i < n; i++) {
            value += this->data[i] * v[i];
        }
        return value;
    }

    inline T dot() const {
        return this->dot(*this);
    }

    inline T norm() const {
        return (T)sqrt((double)this->dot());
    }


    Vector<T, n> abs() const {
        Vector<T, n> dst;

        for (i32u i = 0; i < n; i++) {
            dst[i] = this->data[i] >= 0 ? this->data[i] : -this->data[i];
        }
        return dst;
    }

    Vector<T, n> & abs() {
        for (i32u i = 0; i < n; i++) {
            if (this->data[i] >= 0) {
                this->data[i] = -this->data[i];
            }
        }
        return *this;
    }


    bool null() const {
        for (i32u i = 0; i < n; i++) {
            if (this->data[i] != 0) {
                return false;
            }
        }
        return true;
    }

    Vector<T, n> & fill(T value) {
        for (i32u i = 0; i < n; i++) {
            this->data[i] = value;
        }
        return *this;
    }

    Vector<T, n> & zero() {
        return this->fill(0);
    }
};


#endif //__MATH_H_INCLUDE__