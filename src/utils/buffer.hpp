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


    VertexAttributeBuffer(i32u vertexCount, i32u stride, GLenum usage = GL_STATIC_DRAW) : Buffer(GL_ARRAY_BUFFER, this->vertexCount * this->stride, NULL, usage), vertexCount(vertexCount), stride(stride) {
    }

    VertexAttributeBuffer(const VertexAttributeBuffer &buffer) : Buffer(buffer), vertexCount(buffer.vertexCount), stride(buffer.stride) {
    }

    virtual ~VertexAttributeBuffer() {
    }
};


class ElementBuffer : public Buffer {
public:
    const i32u elementCount;
    const i32u vertexCount;
    const i32u indexSize;


    ElementBuffer(i32u elementCount, i32u vertexCount, i32u indexSize, GLenum usage = GL_STATIC_DRAW) : Buffer(GL_ELEMENT_ARRAY_BUFFER, this->elementCount * this->vertexCount * this->indexSize, NULL, usage), elementCount(elementCount), vertexCount(vertexCount), indexSize(indexSize) {
    }

    ElementBuffer(const ElementBuffer &buffer) : Buffer(buffer), elementCount(buffer.elementCount), vertexCount(buffer.vertexCount), indexSize(buffer.indexSize) {
    }

    virtual ~ElementBuffer() {
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
        {
            i8u *buffer = (i8u*)this->map(vertexOffset * this->stride, this->stride);

            if (buffer == NULL) {
                return;
            }
            memcpy(buffer, vertex.position.data, vertexCoords * sizeof(VT));
            buffer += vertexCoords * sizeof(VT);
            this->unmap();
        }
        this->disable();
    }
    virtual void setVertices(i32u vertexOffset, const std::vector<V> &data) {
        this->enable();
        {
            i8u *buffer = (i8u*)this->map(vertexOffset * this->stride, data.size() * this->stride);

            if (buffer == NULL) {
                return;
            }
            std::for_each(data.begin(), data.end(), [&] (const V &vertex) {
                memcpy(buffer, vertex.position.data, vertexCoords * sizeof(VT));
                buffer += vertexCoords * sizeof(VT);
            });
            this->unmap();
        }
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
        {
            i8u *buffer = (i8u*)this->map(vertexOffset * this->stride, this->stride);

            if (buffer == NULL) {
                return;
            }
            memcpy(buffer, vertex.position.data, vertexCoords * sizeof(VT));
            buffer += vertexCoords * sizeof(VT);
            memcpy(buffer, vertex.normal.data,   normalCoords * sizeof(NT));
            buffer += normalCoords * sizeof(NT);
            this->unmap();
        }
        this->disable();
    }
    virtual void setVertices(i32u vertexOffset, const std::vector<Vertex> &data) {
        this->enable();
        {
            i8u *buffer = (i8u*)this->map(vertexOffset * this->stride, data.size() * this->stride);

            if (buffer == NULL) {
                return;
            }
            std::for_each(data.begin(), data.end(), [&] (const Vertex &vertex) {
                memcpy(buffer, vertex.position.data, vertexCoords * sizeof(VT));
                buffer += vertexCoords * sizeof(VT);
                memcpy(buffer, vertex.normal.data,   normalCoords * sizeof(NT));
                buffer += normalCoords * sizeof(NT);
            });
            this->unmap();
        }
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
        {
            i8u *buffer = (i8u*)this->map(vertexOffset * this->stride, this->stride);

            if (buffer == NULL) {
                return;
            }
            memcpy(buffer, vertex.position.data, vertexCoords * sizeof(VT));
            buffer += vertexCoords * sizeof(VT);
            memcpy(buffer, vertex.normal.data,   normalCoords * sizeof(NT));
            buffer += normalCoords * sizeof(NT);
            memcpy(buffer, vertex.color.data,    colorCoords * sizeof(CT));
            buffer += colorCoords * sizeof(CT);
            this->unmap();
        }
        this->disable();
    }
    virtual void setVertices(i32u vertexOffset, const std::vector<Vertex> &data) {
        this->enable();
        {
            i8u *buffer = (i8u*)this->map(vertexOffset * this->stride, data.size() * this->stride);

            if (buffer == NULL) {
                return;
            }
            std::for_each(data.begin(), data.end(), [&] (const Vertex &vertex) {
                memcpy(buffer, vertex.position.data, vertexCoords * sizeof(VT));
                buffer += vertexCoords * sizeof(VT);
                memcpy(buffer, vertex.normal.data,   normalCoords * sizeof(NT));
                buffer += normalCoords * sizeof(NT);
                memcpy(buffer, vertex.color.data,    colorCoords * sizeof(CT));
                buffer += colorCoords * sizeof(CT);
            });
            this->unmap();
        }
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
        {
            i8u *buffer = (i8u*)this->map(vertexOffset * this->stride, this->stride);

            if (buffer == NULL) {
                return;
            }
            memcpy(buffer, vertex.position.data, vertexCoords * sizeof(VT));
            buffer += vertexCoords * sizeof(VT);
            memcpy(buffer, vertex.normal.data,   normalCoords * sizeof(NT));
            buffer += normalCoords * sizeof(NT);
            memcpy(buffer, vertex.texture.data,  textureCoords * sizeof(TT));
            buffer += textureCoords * sizeof(TT);
            this->unmap();
        }
        this->disable();
    }
    virtual void setVertices(i32u vertexOffset, const std::vector<Vertex> &data) {
        this->enable();
        {
            i8u *buffer = (i8u*)this->map(vertexOffset * this->stride, data.size() * this->stride);

            if (buffer == NULL) {
                return;
            }
            std::for_each(data.begin(), data.end(), [&] (const Vertex &vertex) {
                memcpy(buffer, vertex.position.data, vertexCoords * sizeof(VT));
                buffer += vertexCoords * sizeof(VT);
                memcpy(buffer, vertex.normal.data,   normalCoords * sizeof(NT));
                buffer += normalCoords * sizeof(NT);
                memcpy(buffer, vertex.texture.data,  textureCoords * sizeof(TT));
                buffer += textureCoords * sizeof(TT);
            });
            this->unmap();
        }
        this->disable();
    }
};


#endif //__BUFFER_H_INCLUDE__