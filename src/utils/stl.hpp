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

#ifndef __STL_H_INCLUDE__
#define __STL_H_INCLUDE__


template<class T>
class LazyInitialized {
private:
    function<void(T&)> initializer;
    bool initialized;
    T value;


    LazyInitialized() {
    }


public:
    inline LazyInitialized(const function<void(T&)> &initializer) : initializer(initializer), initialized(false) {
    }

    inline LazyInitialized(const LazyInitialized<T> &ref) : initializer(ref.initializer), initialized(ref.initialized), value(ref.value) {
    }


    LazyInitialized<T> & operator =(const LazyInitialized<T> &ref) {
        this->initializer = ref.initializer;
        this->initialized = ref.initialized;
        this->value = ref.value;
        return *this;
    }


    inline T &operator *() {
        if (!this->initialized) {
            this->initializer(this->value);
            this->initialized = true;
        }
        return this->value;
    }

    inline const T &operator *() const {
        if (!this->initialized) {
            this->initializer(this->value);
            this->initialized = true;
        }
        return this->value;
    }
};


template<class M>
class map_key_iterator : public M::iterator {
public:
    typedef typename M::iterator IT;
    typedef typename M::value_type::first_type KT;


    map_key_iterator(const IT &it) : M::iterator(it) {
    }


    KT & operator *() {
        return IT::operator *().first;
    }
};

template<class M>
class map_key_const_iterator : public M::const_iterator {
public:
    typedef typename M::const_iterator IT;
    typedef typename M::value_type::first_type KT;


    map_key_const_iterator(const IT &it) : IT(it) {
    }


    KT & operator *() {
        return IT::operator *().first;
    }
};


#endif //__STL_H_INCLUDE__