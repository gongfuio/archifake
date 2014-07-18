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

#include "archifake.hpp"


Buffer::Buffer(GLenum target, i32u size, const GLvoid *data, GLenum usage) : id(GL_ZERO), enabled(0), target(target), size(size), usage(usage) {
    glGenBuffers(1, &this->id);
    if (this->id == GL_ZERO) {
        return;
    }

    if (this->size > 0) {
        glBindBuffer(this->target, this->id);
        glBufferData(this->target, this->size, data, this->usage);
        glBindBuffer(this->target, GL_ZERO);
    }
}

Buffer::Buffer(const Buffer &buffer) : id(GL_ZERO), enabled(0), target(buffer.target), size(buffer.size), usage(buffer.usage) {
    glGenBuffers(1, &this->id);
    if (this->id == GL_ZERO || buffer.id == GL_ZERO) {
        return;
    }

    if (this->size > 0) {
        glBindBuffer(GL_COPY_READ_BUFFER, buffer.id);
        glBindBuffer(GL_COPY_WRITE_BUFFER, this->id);
        glBufferData(GL_COPY_WRITE_BUFFER, this->size, NULL, this->usage);
        glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, this->size);
        glBindBuffer(GL_COPY_WRITE_BUFFER, GL_ZERO);
        glBindBuffer(GL_COPY_READ_BUFFER, GL_ZERO);
    }
}

Buffer::~Buffer() {
    if (this->id != GL_ZERO) {
        glDeleteBuffers(1, &this->id);
    }
}

void Buffer::enable() {
    if (this->enabled == 0) {
        if (this->id == GL_ZERO) {
            return;
        }
        glBindBuffer(this->target, this->id);
    }
    this->enabled++;
}

void Buffer::disable() {
    this->enabled--;
    if (this->enabled == 0) {
        glBindBuffer(this->target, GL_ZERO);
    }
}

void Buffer::getData(i32u offset, i32u size, GLvoid *data) {
    this->enable();

    glGetBufferSubData(this->target, offset, size, data);

    this->disable();
}

void Buffer::setData(i32u offset, i32u size, const GLvoid *data) {
    this->enable();

    glBufferSubData(this->target, offset, size, data);

    this->disable();
}

GLvoid* Buffer::map(i32u access) {
    if (this->enabled == 0) {
        return NULL;
    }
    return glMapBuffer(this->target, access);
}

GLvoid* Buffer::map(i32u offset, i32u size, i32u access) {
    if (this->enabled == 0) {
        return NULL;
    }
    return glMapBufferRange(this->target, offset, size, access);
}

void Buffer::flush(i32u offset, i32u size) {
    if (this->enabled == 0) {
        return;
    }
    glFlushMappedBufferRange(this->target, offset, size);
}

void Buffer::unmap() {
    if (this->enabled == 0) {
        return;
    }
    glUnmapBuffer(this->target);
}
