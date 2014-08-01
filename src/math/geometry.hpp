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

#ifndef __MATH_GEOMETRY_H_INCLUDE__
#define __MATH_GEOMETRY_H_INCLUDE__


template<typename T>
class Rectangle2 {
public:
    typedef Vector<T, 2> V;


private:
    V _tl;
    V _br;


public:
    inline Rectangle2() {
    }

    inline Rectangle2(const T &x1, const T &y1, const T &x2, const T &y2) : _tl(Vector2(_min(x1, x2), _min(y1, y2))), _br(Vector2(_max(x1, x2), _max(y1, y2))) {
    }

    inline Rectangle2(const V &tl, const V &br) : _tl(Vector2(_min(tl[0], br[0]), _min(tl[1], br[1]))), _br(Vector2(_max(tl[0], br[0]), _max(tl[1], br[1]))) {
    }

    inline Rectangle2(const Rectangle2<T> &rect) : _tl(rect._tl), _br(rect._br) {
    }


    int operator ==(const Rectangle2<T> &rect) const {
        return (this->_tl == rect._tl && this->_br == rect._br);
    }

    inline int operator !=(const Rectangle2<T> &rect) const {
        return !(*this == rect);
    }


    inline const V & tl() const {
        return this->_tl;
    }

    inline const V & br() const {
        return this->_br;
    }

    inline const T & x() const {
        return this->_tl[0];
    }

    inline const T & y() const {
        return this->_tl[1];
    }

    inline T width() const {
        return this->_br[0] - this->_tl[0];
    }

    inline T height() const {
        return this->_br[1] - this->_tl[1];
    }


    inline bool isInside(const V &p) const {
        return (this->_tl[0] <= p[0] && p[0] <= this->_br[0] && this->_tl[1] <= p[1] && p[1] <= this->_br[1]);
    }

    inline bool isOutside(const V &p) const {
        return !this->isInside(p);
    }


    void print(const char *name) const {
        printf("%s\n", name);
        this->print();
        printf("\n");
    }

    void print() const {
        printf("Rectangle2: %.05f %.05f, %.05f %.05f\n", (double)this->_tl[0], (double)this->_tl[1], (double)this->width(), (double)this->height());
    }
};


template<typename T, int n>
class Line {
public:
    typedef Vector<T, n> V;


private:
    V _point;
    V _direction;


public:
    inline Line() {
    }

    inline Line(const V &point, const V &direction) : _point(point), _direction(direction) {
    }

    inline Line(const Line<T, n> &line) : _point(line._point), _direction(line._direction) {
    }


    int operator ==(const Line<T, n> &line) const {
        return (this->_point == line._point && this->_direction == line._direction);
    }

    inline int operator !=(const Line<T, n> &line) const {
        return !(*this == line);
    }


    inline const V & point() const {
        return this->_point;
    }

    inline const V & direction() const {
        return this->_direction;
    }


    void print(const char *name) const {
        printf("%s\n", name);
        this->print();
        printf("\n");
    }

    void print() const {
        printf("Line[%d]\n", n);
        this->_point.print();
        this->_direction.print();
    }
};


#endif //__MATH_GEOMETRY_H_INCLUDE__