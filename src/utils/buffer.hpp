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

#ifndef __BUFFER_H_INCLUDE__
#define __BUFFER_H_INCLUDE__


class Buffer {
protected:
    GLuint buffer;
    GLenum target;
    GLenum usage;
    i32u enabled;


public:
    Buffer(GLenum target = GL_ARRAY_BUFFER, GLenum usage = GL_STATIC_DRAW);
    virtual ~Buffer();


    virtual void init(GLsizeiptr size, GLvoid *data = NULL);
    virtual void update(GLintptr offset, GLsizeiptr size, GLvoid *data);
    virtual void free();

    virtual void enable();
    virtual void disable();
};


class VertexAttributeBuffer : public Buffer {
protected:
    i32u vertexCount;

    i32u stride;


public:
    VertexAttributeBuffer(i32u vertexCount, i32u stride, GLenum usage = GL_STATIC_DRAW) : Buffer(GL_ARRAY_BUFFER, usage), vertexCount(vertexCount), stride(stride) {
        this->init(this->vertexCount * this->stride);
    }

    virtual ~VertexAttributeBuffer() {
    }


    virtual void setVertex(i32u vertexOffset, GLvoid *data);
    virtual void setVertices(i32u vertexOffset, i32u vertexCount, GLvoid *data);
};


class ElementBuffer : public Buffer {
protected:
    i32u elementCount;

    i32u vertexCount;

    i32u indexSize;


public:
    ElementBuffer(i32u elementCount, i32u vertexCount, i32u indexSize, GLenum usage = GL_STATIC_DRAW) : Buffer(GL_ELEMENT_ARRAY_BUFFER, usage), elementCount(elementCount), vertexCount(vertexCount), indexSize(indexSize) {
        this->init(this->elementCount * this->vertexCount * this->indexSize);
    }

    virtual ~ElementBuffer() {
    }


    virtual void setElement(i32u elementOffset, GLvoid *data);
    virtual void setElements(i32u elementOffset, i32u elementCount, GLvoid *data);
};


#endif //__SURFACE_H_INCLUDE__