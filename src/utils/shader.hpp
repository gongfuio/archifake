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

#ifndef __SHADER_H_INCLUDE__
#define __SHADER_H_INCLUDE__


class ShaderProgram;

class Shader {
protected:
    friend class ShaderProgram;


    GLuint id;
    bool compiled;
    string logs;


public:
    const i32u type;
    const string source;


    Shader(i32u type, const string &source);
    ~Shader();


    bool isCompiled() const;
    const string & getLogs() const;
};


class ShaderProgram {
public:
    typedef struct {
        string name;
        GLint location;
        GLint uniforms;
        GLint size;
    } UniformBlock;

    typedef struct {
        string name;
        GLint location;
        GLenum type;
        GLint size;
        string blockName;
        GLint blockOffset;
        GLint arrayStride;
        GLint matrixStride;
        bool rowMajor;
        // GLint atomicCounterBufferIndex;
    } Uniform;

    typedef struct {
        string name;
        GLint location;
        GLenum type;
        GLint size;
    } Attribute;


protected:
    GLuint id;
    bool linked;
    bool validated;
    string linkerLogs;
    string validatorLogs;
    map<string, UniformBlock> uniformBlocks;
    map<string, Uniform> uniforms;
    map<string, Attribute> attributes;
    i32u enabled;


    void link(const list<shared_ptr<Shader> > &shaders);


public:
    ShaderProgram(const shared_ptr<Shader> &vertexShader, const shared_ptr<Shader> &fragmentShader);
    ShaderProgram(const list<shared_ptr<Shader> > &shaders);
    ~ShaderProgram();


    bool isLinked() const;
    bool isValidated() const;
    const string & getLinkerLogs() const;
    const string & getValidatorLogs() const;

    void enable();
    void disable();

    GLint uniformLocation(const string &name) const;
    GLint attributeLocation(const string &name) const;

    void uniform(GLint location, i32 value);
    void uniform(GLint location, const Vector<i32, 2> &vec);
    void uniform(GLint location, const Vector<i32, 3> &vec);
    void uniform(GLint location, const Vector<i32, 4> &vec);
    void uniform(GLint location, const vector<i32> &values);
    void uniform(GLint location, const vector<Vector<i32, 2> > &values);
    void uniform(GLint location, const vector<Vector<i32, 3> > &values);
    void uniform(GLint location, const vector<Vector<i32, 4> > &values);

    void uniform(GLint location, f32 value);
    void uniform(GLint location, const Vector<f32, 2> &vec);
    void uniform(GLint location, const Vector<f32, 3> &vec);
    void uniform(GLint location, const Vector<f32, 4> &vec);
    void uniform(GLint location, const vector<f32> &values);
    void uniform(GLint location, const vector<Vector<f32, 2> > &values);
    void uniform(GLint location, const vector<Vector<f32, 3> > &values);
    void uniform(GLint location, const vector<Vector<f32, 4> > &values);

    void uniform(GLint location, const Matrix<f32, 2, 2> &matrix, bool transpose = false);
    void uniform(GLint location, const Matrix<f32, 2, 3> &matrix, bool transpose = false);
    void uniform(GLint location, const Matrix<f32, 2, 4> &matrix, bool transpose = false);
    void uniform(GLint location, const Matrix<f32, 3, 2> &matrix, bool transpose = false);
    void uniform(GLint location, const Matrix<f32, 3, 3> &matrix, bool transpose = false);
    void uniform(GLint location, const Matrix<f32, 3, 4> &matrix, bool transpose = false);
    void uniform(GLint location, const Matrix<f32, 4, 2> &matrix, bool transpose = false);
    void uniform(GLint location, const Matrix<f32, 4, 3> &matrix, bool transpose = false);
    void uniform(GLint location, const Matrix<f32, 4, 4> &matrix, bool transpose = false);

    void uniform(GLint location, const vector<Matrix<f32, 2, 2> > &values, bool transpose = false);
    void uniform(GLint location, const vector<Matrix<f32, 2, 3> > &values, bool transpose = false);
    void uniform(GLint location, const vector<Matrix<f32, 2, 4> > &values, bool transpose = false);
    void uniform(GLint location, const vector<Matrix<f32, 3, 2> > &values, bool transpose = false);
    void uniform(GLint location, const vector<Matrix<f32, 3, 3> > &values, bool transpose = false);
    void uniform(GLint location, const vector<Matrix<f32, 3, 4> > &values, bool transpose = false);
    void uniform(GLint location, const vector<Matrix<f32, 4, 2> > &values, bool transpose = false);
    void uniform(GLint location, const vector<Matrix<f32, 4, 3> > &values, bool transpose = false);
    void uniform(GLint location, const vector<Matrix<f32, 4, 4> > &values, bool transpose = false);
};


#endif //__SHADER_H_INCLUDE__