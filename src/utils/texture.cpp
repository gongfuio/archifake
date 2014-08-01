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


Texture::Texture(GLenum target, GLsizei levels, const GLenum format, GLsizei width, GLsizei height, GLsizei depth) : id(GL_ZERO), enabled(0), target(target), levels(levels), format(format), width(width), height(height), depth(depth) {
    glGenTextures(1, &this->id);
    if (this->id == GL_ZERO) {
        return;
    }

    glBindTexture(this->target, this->id);
    switch (this->target) {
    case GL_TEXTURE_1D:
    // case GL_PROXY_TEXTURE_1D:
        glTexStorage1D(this->target, this->levels, this->format, this->width);
        break;

    case GL_TEXTURE_2D:
    // case GL_PROXY_TEXTURE_2D:
    case GL_TEXTURE_1D_ARRAY:
    // case GL_PROXY_TEXTURE_1D_ARRAY:
    case GL_TEXTURE_RECTANGLE:
    // case GL_PROXY_TEXTURE_RECTANGLE:
    case GL_TEXTURE_CUBE_MAP:
    // case GL_PROXY_TEXTURE_CUBE_MAP:
        glTexStorage2D(this->target, this->levels, this->format, this->width, this->height);
        break;

    case GL_TEXTURE_2D_MULTISAMPLE:
    // case GL_PROXY_TEXTURE_2D_MULTISAMPLE:
        glTexStorage2DMultisample(this->target, this->levels, this->format, this->width, this->height, GL_FALSE);
        break;

    case GL_TEXTURE_3D:
    // case GL_PROXY_TEXTURE_3D
    case GL_TEXTURE_2D_ARRAY:
    // case GL_PROXY_TEXTURE_2D_ARRAY:
    case GL_TEXTURE_CUBE_MAP_ARRAY:
    // case GL_PROXY_TEXTURE_CUBE_ARRAY:
        glTexStorage3D(this->target, this->levels, this->format, this->width, this->height, this->depth);
        break;

    case GL_TEXTURE_2D_MULTISAMPLE_ARRAY:
    // case GL_PROXY_TEXTURE_2D_MULTISAMPLE_MULTISAMPLE:
        glTexStorage3DMultisample(this->target, this->levels, this->format, this->width, this->height, this->depth, GL_FALSE);
        break;

    default:
        fprintf(stderr, "ERROR: Unsupported texture target (%d)\n", this->target);
        break;
    }
    glBindTexture(this->target, GL_ZERO);

    // case GL_TEXTURE_BUFFER:

}

Texture::~Texture() {
    if (this->id != GL_ZERO) {
        glDeleteTextures(1, &this->id);
    }
}

void Texture::enable() {
    if (this->enabled == 0) {
        if (this->id == GL_ZERO) {
            return;
        }
        glBindTexture(this->target, this->id);
    }
    this->enabled++;
}
void Texture::disable() {
    this->enabled--;
    if (this->enabled == 0) {
        glBindTexture(this->target, GL_ZERO);
    }
}


shared_ptr<Texture> Texture::new1D(GLsizei levels, const GLenum format, GLsizei width) {
    return shared_ptr<Texture>(new Texture(GL_TEXTURE_1D, levels, format, width, 1, 1));
}
shared_ptr<Texture> Texture::new1DArray(GLsizei levels, const GLenum format, GLsizei width, GLsizei count) {
    return shared_ptr<Texture>(new Texture(GL_TEXTURE_1D_ARRAY, levels, format, width, count, 1));
}

shared_ptr<Texture> Texture::new2D(GLsizei levels, const GLenum format, GLsizei width, GLsizei height) {
    return shared_ptr<Texture>(new Texture(GL_TEXTURE_2D, levels, format, width, height, 1));
}
shared_ptr<Texture> Texture::new2DArray(GLsizei levels, const GLenum format, GLsizei width, GLsizei height, GLsizei count) {
    return shared_ptr<Texture>(new Texture(GL_TEXTURE_2D_ARRAY, levels, format, width, height, count));
}
shared_ptr<Texture> Texture::newRectangle(GLsizei levels, const GLenum format, GLsizei width, GLsizei height) {
    return shared_ptr<Texture>(new Texture(GL_TEXTURE_RECTANGLE, levels, format, width, height, 1));
}
shared_ptr<Texture> Texture::newCubemap(GLsizei levels, const GLenum format, GLsizei width, GLsizei height) {
    return shared_ptr<Texture>(new Texture(GL_TEXTURE_CUBE_MAP, levels, format, width, height, 1));
}

shared_ptr<Texture> Texture::new3D(GLsizei levels, const GLenum format, GLsizei width, GLsizei height, GLsizei depth) {
    return shared_ptr<Texture>(new Texture(GL_TEXTURE_3D, levels, format, width, height, depth));
}

shared_ptr<Texture> Texture::new2DMultisample(GLsizei samples, const GLenum format, GLsizei width, GLsizei height) {
    return shared_ptr<Texture>(new Texture(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, 1));
}
shared_ptr<Texture> Texture::new2DMultisampleArray(GLsizei samples, const GLenum format, GLsizei width, GLsizei height, GLsizei count) {
    return shared_ptr<Texture>(new Texture(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, samples, format, width, height, count));
}
