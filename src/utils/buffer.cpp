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

#include "archifake.hpp"


Buffer::Buffer(GLenum target, GLenum usage) : target(target), usage(usage), enabled(0) {
    glGenBuffers(1, &this->buffer);
}

Buffer::~Buffer() {
    glDeleteBuffers(1, &this->buffer);
}


void Buffer::init(GLsizeiptr size, GLvoid *data) {
    this->enable();
    glBufferData(this->target, size, data, this->usage);
    this->disable();
}

void Buffer::update(GLintptr offset, GLsizeiptr size, GLvoid *data) {
    this->enable();
    glBufferSubData(this->target, offset, size, data);
    this->disable();
}

void Buffer::free() {
    this->enable();
    glBufferData(this->target, 0, NULL, this->usage);
    this->disable();
}


void Buffer::enable() {
    if (this->enabled == 0) {
        glBindBuffer(this->target, this->buffer);
    }
    this->enabled++;
}

void Buffer::disable() {
    this->enabled--;
    if (this->enabled == 0) {
        glBindBuffer(this->target, GL_ZERO);
    }
}


void VertexAttributeBuffer::setVertex(i32u vertexOffset, GLvoid *data) {
    this->enable();
    glBufferSubData(this->target, vertexOffset * this->stride, this->stride, data);
    this->disable();
}

void VertexAttributeBuffer::setVertices(i32u vertexOffset, i32u vertexCount, GLvoid *data) {
    this->enable();
    glBufferSubData(this->target, vertexOffset * this->stride, vertexCount * this->stride, data);
    this->disable();
}


void ElementBuffer::setElement(i32u elementOffset, GLvoid *data) {
    this->enable();
    glBufferSubData(this->target, elementOffset * this->vertexCount * this->indexSize, this->vertexCount * this->indexSize, data);
    this->disable();
}

void ElementBuffer::setElements(i32u elementOffset, i32u elementCount, GLvoid *data) {
    this->enable();
    glBufferSubData(this->target, elementOffset * this->vertexCount * this->indexSize, elementCount * this->vertexCount * this->indexSize, data);
    this->disable();
}
