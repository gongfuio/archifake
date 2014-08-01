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

#ifndef __TEXTURE_H_INCLUDE__
#define __TEXTURE_H_INCLUDE__


class Texture {
protected:
    GLuint id;
    i32 enabled;


    Texture(GLenum target, GLsizei levels, const GLenum format, GLsizei width, GLsizei height, GLsizei depth);


public:
    const GLenum target;
    const GLsizei levels;
    const GLenum format;
    const GLsizei width;
    const GLsizei height;
    const GLsizei depth;


    virtual ~Texture();


    virtual void enable();
    virtual void disable();


    static shared_ptr<Texture> new1D(GLsizei levels, const GLenum format, GLsizei width);
    static shared_ptr<Texture> new1DArray(GLsizei levels, const GLenum format, GLsizei width, GLsizei count);

    static shared_ptr<Texture> new2D(GLsizei levels, const GLenum format, GLsizei width, GLsizei height);
    static shared_ptr<Texture> new2DArray(GLsizei levels, const GLenum format, GLsizei width, GLsizei height, GLsizei count);
    static shared_ptr<Texture> newRectangle(GLsizei levels, const GLenum format, GLsizei width, GLsizei height);
    static shared_ptr<Texture> newCubemap(GLsizei levels, const GLenum format, GLsizei width, GLsizei height);

    static shared_ptr<Texture> new3D(GLsizei levels, const GLenum format, GLsizei width, GLsizei height, GLsizei depth);

    static shared_ptr<Texture> new2DMultisample(GLsizei samples, const GLenum format, GLsizei width, GLsizei height);
    static shared_ptr<Texture> new2DMultisampleArray(GLsizei samples, const GLenum format, GLsizei width, GLsizei height, GLsizei count);


    // static shared_ptr<Texture> fromFile(const string &path);
};


#endif //__TEXTURE_H_INCLUDE__