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

#ifndef __MATH_MISC_H_INCLUDE__
#define __MATH_MISC_H_INCLUDE__


template<typename T>
class Range {
private:
    T _minimum;
    T _maximum;


public:
    inline Range() : _minimum(T(0)), _maximum(T(0)) {
    }

    inline Range(const T &minimum, const T &maximum) : _minimum(minimum), _maximum(maximum) {
    }

    inline Range(const Range<T> &range) : _minimum(range._minimum), _maximum(range._maximum) {
    }


    Range<T> & operator =(const Range<T> &range) {
        this->_minimum = range._minimum;
        this->_maximum = range._maximum;
        return *this;
    }


    int operator ==(const Range<T> &range) const {
        return (_eq(this->_minimum, range._minimum) && _eq(this->_maximum, range._maximum));
    }

    inline int operator !=(const Range<T> &range) const {
        return !(*this == range);
    }


    inline const T & minimum() const {
        return this->_minimum;
    }

    inline const T & maximum() const {
        return this->_maximum;
    }


    inline bool isInside(const T &value) const {
        return (this->_minimum <= value && value <= this->_maximum);
    }

    inline bool isOutside(const T &value) const {
        return !this->isInside(value);
    }


    void print(const char *name) const {
        printf("%s\n", name);
        this->print();
        printf("\n");
    }

    void print() const {
        printf("Range: %.05f %.05f\n", (double)this->_minimum, (double)this->_maximum);
    }
};


template<typename T>
class RGB {
private:
    T _r;
    T _g;
    T _b;


public:
    inline RGB() : _r(T(0)), _g(T(0)), _b(T(0)) {
    }

    inline RGB(const T &r, const T &g, const T &b) : _r(r), _g(g), _b(b) {
    }

    inline RGB(const RGB<T> &color) : _r(color._r), _g(color._g), _b(color._b) {
    }


    RGB<T> & operator =(const RGB<T> &color) {
        this->_r = color._r;
        this->_g = color._g;
        this->_b = color._b;
        return *this;
    }


    int operator ==(const RGB<T> &color) const {
        return (_eq(this->_r, color._r) && _eq(this->_g, color._g) && _eq(this->_b, color._b));
    }

    inline int operator !=(const RGB<T> &color) const {
        return !(*this == color);
    }


    inline const T & r() const {
        return this->_r;
    }

    inline const T & g() const {
        return this->_g;
    }

    inline const T & b() const {
        return this->_b;
    }


    void print(const char *name) const {
        printf("%s\n", name);
        this->print();
        printf("\n");
    }

    void print() const {
        printf("RGB: %.05f %.05f %.05f\n", (double)this->_r, (double)this->_g, (double)this->_b);
    }
};


template<typename T>
class RGBA {
private:
    T _r;
    T _g;
    T _b;
    T _a;


public:
    inline RGBA() : _r(T(0)), _g(T(0)), _b(T(0)), _a(T(0)) {
    }

    inline RGBA(const T &r, const T &g, const T &b, const T &a) : _r(r), _g(g), _b(b), _a(a) {
    }

    inline RGBA(const RGBA<T> &color) : _r(color._r), _g(color._g), _b(color._b), _a(color._a) {
    }


    RGBA<T> & operator =(const RGBA<T> &color) {
        this->_r = color._r;
        this->_g = color._g;
        this->_b = color._b;
        this->_a = color._a;
        return *this;
    }


    int operator ==(const RGBA<T> &color) const {
        return (_eq(this->_r, color._r) && _eq(this->_g, color._g) && _eq(this->_b, color._b) && _eq(this->_a, color._a));
    }

    inline int operator !=(const RGBA<T> &color) const {
        return !(*this == color);
    }


    inline const T & r() const {
        return this->_r;
    }

    inline const T & g() const {
        return this->_g;
    }

    inline const T & b() const {
        return this->_b;
    }

    inline const T & a() const {
        return this->_a;
    }


    void print(const char *name) const {
        printf("%s\n", name);
        this->print();
        printf("\n");
    }

    void print() const {
        printf("RGBA: %.05f %.05f %.05f %.05f\n", (double)this->_r, (double)this->_g, (double)this->_b, (double)this->_a);
    }
};


#endif //__MATH_MISC_H_INCLUDE__