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

#ifndef __BUFFER_H_INCLUDE__
#define __BUFFER_H_INCLUDE__


class Buffer {
private:
    GLuint id;
    i32u enabled;


protected:
    virtual GLvoid * map(i32u access);
    virtual GLvoid * map(i32u offset, i32u size, i32u access);
    void flush(i32u offset, i32u size);
    void unmap();


public:
    const GLenum target;
    const i32u size;
    const GLenum usage;


    Buffer(GLenum target, i32u size, const GLvoid *data = NULL, GLenum usage = GL_STATIC_DRAW);
    Buffer(const Buffer &buffer);
    virtual ~Buffer();


    virtual void enable();
    virtual void disable();

    virtual void getData(i32u offset, i32u size, GLvoid *data);
    virtual void setData(i32u offset, i32u size, const GLvoid *data);
};


class VertexAttributeBuffer : public Buffer {
public:
    const i32u vertexCount;
    const i32u stride;


    VertexAttributeBuffer(i32u vertexCount, i32u stride, GLenum usage = GL_STATIC_DRAW) : Buffer(GL_ARRAY_BUFFER, vertexCount * stride, NULL, usage), vertexCount(vertexCount), stride(stride) {
    }

    VertexAttributeBuffer(const VertexAttributeBuffer &buffer) : Buffer(buffer), vertexCount(buffer.vertexCount), stride(buffer.stride) {
    }

    virtual ~VertexAttributeBuffer() {
    }
};


template<typename VT, int vertexCoords>
class VertexAttributeBufferV : public VertexAttributeBuffer {
public:
    typedef Vector<VT, vertexCoords> V;


    VertexAttributeBufferV(i32u vertexCount, GLenum usage = GL_STATIC_DRAW) : VertexAttributeBuffer(
        vertexCount,
        vertexCoords * sizeof(VT),
        usage
    ) { }

    VertexAttributeBufferV(const VertexAttributeBufferV &buffer) : VertexAttributeBuffer(buffer) {
    }

    virtual ~VertexAttributeBufferV() { }


    virtual void setVertex(i32u vertexOffset, const V &vertex) {
        this->enable();
        vertexOffset *= this->stride;
        this->setData(vertexOffset, this->stride, vertex);
        // vertexOffset += this->stride;
        this->disable();
    }
    virtual void setVertices(i32u vertexOffset, const vector<V> &data) {
        this->enable();
        vertexOffset *= this->stride;
        for_each(data.begin(), data.end(), [&] (const V &vertex) {
            this->setData(vertexOffset, this->stride, vertex);
            vertexOffset += this->stride;
        });
        this->disable();
    }
};


template<typename VT, int vertexCoords, typename NT, int normalCoords>
class VertexAttributeBufferVN : public VertexAttributeBuffer {
public:
    typedef Vector<VT, vertexCoords> V;
    typedef Vector<NT, normalCoords> N;

    typedef struct {
        V position;
        N normal;
    } Vertex;


    VertexAttributeBufferVN(i32u vertexCount, GLenum usage = GL_STATIC_DRAW) : VertexAttributeBuffer(
        vertexCount,
        vertexCoords * sizeof(VT) + normalCoords * sizeof(NT),
        usage
    ) { }

    VertexAttributeBufferVN(const VertexAttributeBufferVN &buffer) : VertexAttributeBuffer(buffer) {
    }

    virtual ~VertexAttributeBufferVN() { }


    virtual void setVertex(i32u vertexOffset, const Vertex &vertex) {
        this->enable();
        vertexOffset *= this->stride;
        this->setData(vertexOffset, vertexCoords * sizeof(VT), vertex.position);
        vertexOffset += vertexCoords * sizeof(VT);
        this->setData(vertexOffset, normalCoords * sizeof(NT), vertex.normal);
        // vertexOffset += normalCoords * sizeof(NT);
        this->disable();
    }
    virtual void setVertices(i32u vertexOffset, const vector<Vertex> &data) {
        this->enable();
        vertexOffset *= this->stride;
        for_each(data.begin(), data.end(), [&] (const Vertex &vertex) {
            this->setData(vertexOffset, vertexCoords * sizeof(VT), vertex.position);
            vertexOffset += vertexCoords * sizeof(VT);
            this->setData(vertexOffset, normalCoords * sizeof(NT), vertex.normal);
            vertexOffset += normalCoords * sizeof(NT);
        });
        this->disable();
    }
};


template<typename VT, int vertexCoords, typename NT, int normalCoords, typename CT, int colorCoords>
class VertexAttributeBufferVNC : public VertexAttributeBuffer {
public:
    typedef Vector<VT, vertexCoords> V;
    typedef Vector<NT, normalCoords> N;
    typedef Vector<CT, colorCoords> C;

    typedef struct {
        V position;
        N normal;
        C color;
    } Vertex;


    VertexAttributeBufferVNC(i32u vertexCount, GLenum usage = GL_STATIC_DRAW) : VertexAttributeBuffer(
        vertexCount,
        vertexCoords * sizeof(VT) + normalCoords * sizeof(NT) + colorCoords * sizeof(CT),
        usage
    ) { }

    VertexAttributeBufferVNC(const VertexAttributeBufferVNC &buffer) : VertexAttributeBuffer(buffer) {
    }

    virtual ~VertexAttributeBufferVNC() { }


    virtual void setVertex(i32u vertexOffset, const Vertex &vertex) {
        this->enable();
        vertexOffset *= this->stride;
        this->setData(vertexOffset, vertexCoords * sizeof(VT), vertex.position);
        vertexOffset += vertexCoords * sizeof(VT);
        this->setData(vertexOffset, normalCoords * sizeof(NT), vertex.normal);
        vertexOffset += normalCoords * sizeof(NT);
        this->setData(vertexOffset, colorCoords * sizeof(CT), vertex.color);
        // vertexOffset += colorCoords * sizeof(CT);
        this->disable();
    }
    virtual void setVertices(i32u vertexOffset, const vector<Vertex> &data) {
        this->enable();
        vertexOffset *= this->stride;
        for_each(data.begin(), data.end(), [&] (const Vertex &vertex) {
            this->setData(vertexOffset, vertexCoords * sizeof(VT), vertex.position);
            vertexOffset += vertexCoords * sizeof(VT);
            this->setData(vertexOffset, normalCoords * sizeof(NT), vertex.normal);
            vertexOffset += normalCoords * sizeof(NT);
            this->setData(vertexOffset, colorCoords * sizeof(CT), vertex.color);
            vertexOffset += colorCoords * sizeof(CT);
        });
        this->disable();
    }
};


template<typename VT, int vertexCoords, typename NT, int normalCoords, typename TT, int textureCoords>
class VertexAttributeBufferVNT : public VertexAttributeBuffer {
public:
    typedef Vector<VT, vertexCoords>  V;
    typedef Vector<NT, normalCoords>  N;
    typedef Vector<TT, textureCoords> T;

    typedef struct {
        V position;
        N normal;
        T texture;
    } Vertex;


    VertexAttributeBufferVNT(i32u vertexCount, GLenum usage = GL_STATIC_DRAW) : VertexAttributeBuffer(
        vertexCount,
        vertexCoords * sizeof(VT) + normalCoords * sizeof(NT) + textureCoords * sizeof(TT),
        usage
    ) { }

    VertexAttributeBufferVNT(const VertexAttributeBufferVNT &buffer) : VertexAttributeBuffer(buffer) {
    }

    virtual ~VertexAttributeBufferVNT() { }


    virtual void setVertex(i32u vertexOffset, const Vertex &vertex) {
        this->enable();
        vertexOffset *= this->stride;
        this->setData(vertexOffset, vertexCoords * sizeof(VT), vertex.position);
        vertexOffset += vertexCoords * sizeof(VT);
        this->setData(vertexOffset, normalCoords * sizeof(NT), vertex.normal);
        vertexOffset += normalCoords * sizeof(NT);
        this->setData(vertexOffset, textureCoords * sizeof(TT), vertex.texture);
        // vertexOffset += textureCoords * sizeof(TT);
        this->disable();
    }
    virtual void setVertices(i32u vertexOffset, const vector<Vertex> &data) {
        this->enable();
        vertexOffset *= this->stride;
        for_each(data.begin(), data.end(), [&] (const Vertex &vertex) {
            this->setData(vertexOffset, vertexCoords * sizeof(VT), vertex.position);
            vertexOffset += vertexCoords * sizeof(VT);
            this->setData(vertexOffset, normalCoords * sizeof(NT), vertex.normal);
            vertexOffset += normalCoords * sizeof(NT);
            this->setData(vertexOffset, textureCoords * sizeof(TT), vertex.texture);
            vertexOffset += textureCoords * sizeof(TT);
        });
        this->disable();
    }
};


template<typename IT, int vertexCount>
class ElementBuffer : public Buffer {
public:
    typedef struct {
        IT indices[vertexCount];
    } F;


    const i32u faceCount;
    const i32u stride;


    ElementBuffer(i32u faceCount, GLenum usage = GL_STATIC_DRAW) : Buffer(GL_ELEMENT_ARRAY_BUFFER, faceCount * vertexCount * sizeof(IT), NULL, usage), faceCount(faceCount), stride(vertexCount * sizeof(IT)) {
    }

    ElementBuffer(const ElementBuffer &buffer) : Buffer(buffer), faceCount(buffer.faceCount), stride(buffer.stride) {
    }

    virtual ~ElementBuffer() {
    }


    virtual void setFace(i32u faceOffset, const F &face) {
        this->enable();
        faceOffset *= this->stride;
        this->setData(faceOffset, this->stride, face.indices);
        // faceOffset += this->stride;
        this->disable();
    }
    virtual void setFaces(i32u faceOffset, const vector<F> &data) {
        this->enable();
        faceOffset *= this->stride;
        for_each(data.begin(), data.end(), [&] (const F &face) {
            this->setData(faceOffset, this->stride, face.indices);
            faceOffset += this->stride;
        });
        this->disable();
    }
};


#endif //__BUFFER_H_INCLUDE__