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
    static const UniformBlock emptyUniformBlock;
    static const Uniform emptyUniform;
    static const Attribute emptyAttribute;


    GLuint id;
    bool linked;
    bool validated;
    i32u enabled;
    list<shared_ptr<Shader> > shaders;
    string linkerLogs;
    string validatorLogs;
    map<string, UniformBlock> uniformBlocks;
    map<string, Uniform> uniforms;
    map<string, Attribute> attributes;


    void link();


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

    set<string> uniformBlockNames() const;
    set<string> uniformNames() const;
    set<string> attributeNames() const;

    const UniformBlock & uniformBlock(const string &name) const;
    const Uniform & uniform(const string &name) const;
    const Attribute & attribute(const string &name) const;

    GLint uniformBlockLocation(const string &name) const;
    GLint uniformLocation(const string &name) const;
    GLint attributeLocation(const string &name) const;

    void uniform(GLint location, i32 value) const;
    void uniform(GLint location, const Vector<i32, 2> &vec) const;
    void uniform(GLint location, const Vector<i32, 3> &vec) const;
    void uniform(GLint location, const Vector<i32, 4> &vec) const;
    void uniform(GLint location, const vector<i32> &values) const;
    void uniform(GLint location, const vector<Vector<i32, 2> > &values) const;
    void uniform(GLint location, const vector<Vector<i32, 3> > &values) const;
    void uniform(GLint location, const vector<Vector<i32, 4> > &values) const;

    void uniform(GLint location, f32 value) const;
    void uniform(GLint location, const Vector<f32, 2> &vec) const;
    void uniform(GLint location, const Vector<f32, 3> &vec) const;
    void uniform(GLint location, const Vector<f32, 4> &vec) const;
    void uniform(GLint location, const vector<f32> &values) const;
    void uniform(GLint location, const vector<Vector<f32, 2> > &values) const;
    void uniform(GLint location, const vector<Vector<f32, 3> > &values) const;
    void uniform(GLint location, const vector<Vector<f32, 4> > &values) const;

    void uniform(GLint location, const Matrix<f32, 2, 2> &matrix, bool transpose = false) const;
    void uniform(GLint location, const Matrix<f32, 2, 3> &matrix, bool transpose = false) const;
    void uniform(GLint location, const Matrix<f32, 2, 4> &matrix, bool transpose = false) const;
    void uniform(GLint location, const Matrix<f32, 3, 2> &matrix, bool transpose = false) const;
    void uniform(GLint location, const Matrix<f32, 3, 3> &matrix, bool transpose = false) const;
    void uniform(GLint location, const Matrix<f32, 3, 4> &matrix, bool transpose = false) const;
    void uniform(GLint location, const Matrix<f32, 4, 2> &matrix, bool transpose = false) const;
    void uniform(GLint location, const Matrix<f32, 4, 3> &matrix, bool transpose = false) const;
    void uniform(GLint location, const Matrix<f32, 4, 4> &matrix, bool transpose = false) const;

    void uniform(GLint location, const vector<Matrix<f32, 2, 2> > &values, bool transpose = false) const;
    void uniform(GLint location, const vector<Matrix<f32, 2, 3> > &values, bool transpose = false) const;
    void uniform(GLint location, const vector<Matrix<f32, 2, 4> > &values, bool transpose = false) const;
    void uniform(GLint location, const vector<Matrix<f32, 3, 2> > &values, bool transpose = false) const;
    void uniform(GLint location, const vector<Matrix<f32, 3, 3> > &values, bool transpose = false) const;
    void uniform(GLint location, const vector<Matrix<f32, 3, 4> > &values, bool transpose = false) const;
    void uniform(GLint location, const vector<Matrix<f32, 4, 2> > &values, bool transpose = false) const;
    void uniform(GLint location, const vector<Matrix<f32, 4, 3> > &values, bool transpose = false) const;
    void uniform(GLint location, const vector<Matrix<f32, 4, 4> > &values, bool transpose = false) const;


    inline void uniform(const string &name, i32 value) const {
        GLint location = this->uniformLocation(name);

        if (location >= 0) {
            this->uniform(location, value);
        }
    }

    inline void uniform(const string &name, const Vector<i32, 2> &vec) const {
        GLint location = this->uniformLocation(name);

        if (location >= 0) {
            this->uniform(location, vec);
        }
    }

    inline void uniform(const string &name, const Vector<i32, 3> &vec) const {
        GLint location = this->uniformLocation(name);

        if (location >= 0) {
            this->uniform(location, vec);
        }
    }

    inline void uniform(const string &name, const Vector<i32, 4> &vec) const {
        GLint location = this->uniformLocation(name);

        if (location >= 0) {
            this->uniform(location, vec);
        }
    }

    inline void uniform(const string &name, const vector<i32> &values) const {
        GLint location = this->uniformLocation(name);

        if (location >= 0) {
            this->uniform(location, values);
        }
    }

    inline void uniform(const string &name, const vector<Vector<i32, 2> > &values) const {
        GLint location = this->uniformLocation(name);

        if (location >= 0) {
            this->uniform(location, values);
        }
    }

    inline void uniform(const string &name, const vector<Vector<i32, 3> > &values) const {
        GLint location = this->uniformLocation(name);

        if (location >= 0) {
            this->uniform(location, values);
        }
    }

    inline void uniform(const string &name, const vector<Vector<i32, 4> > &values) const {
        GLint location = this->uniformLocation(name);

        if (location >= 0) {
            this->uniform(location, values);
        }
    }

    inline void uniform(const string &name, f32 value) const {
        GLint location = this->uniformLocation(name);

        if (location >= 0) {
            this->uniform(location, value);
        }
    }

    inline void uniform(const string &name, const Vector<f32, 2> &vec) const {
        GLint location = this->uniformLocation(name);

        if (location >= 0) {
            this->uniform(location, vec);
        }
    }

    inline void uniform(const string &name, const Vector<f32, 3> &vec) const {
        GLint location = this->uniformLocation(name);

        if (location >= 0) {
            this->uniform(location, vec);
        }
    }

    inline void uniform(const string &name, const Vector<f32, 4> &vec) const {
        GLint location = this->uniformLocation(name);

        if (location >= 0) {
            this->uniform(location, vec);
        }
    }

    inline void uniform(const string &name, const vector<f32> &values) const {
        GLint location = this->uniformLocation(name);

        if (location >= 0) {
            this->uniform(location, values);
        }
    }

    inline void uniform(const string &name, const vector<Vector<f32, 2> > &values) const {
        GLint location = this->uniformLocation(name);

        if (location >= 0) {
            this->uniform(location, values);
        }
    }

    inline void uniform(const string &name, const vector<Vector<f32, 3> > &values) const {
        GLint location = this->uniformLocation(name);

        if (location >= 0) {
            this->uniform(location, values);
        }
    }

    inline void uniform(const string &name, const vector<Vector<f32, 4> > &values) const {
        GLint location = this->uniformLocation(name);

        if (location >= 0) {
            this->uniform(location, values);
        }
    }

    inline void uniform(const string &name, const Matrix<f32, 2, 2> &matrix, bool transpose = false) const {
        GLint location = this->uniformLocation(name);

        if (location >= 0) {
            this->uniform(location, matrix, transpose);
        }
    }

    inline void uniform(const string &name, const Matrix<f32, 2, 3> &matrix, bool transpose = false) const {
        GLint location = this->uniformLocation(name);

        if (location >= 0) {
            this->uniform(location, matrix, transpose);
        }
    }

    inline void uniform(const string &name, const Matrix<f32, 2, 4> &matrix, bool transpose = false) const {
        GLint location = this->uniformLocation(name);

        if (location >= 0) {
            this->uniform(location, matrix, transpose);
        }
    }

    inline void uniform(const string &name, const Matrix<f32, 3, 2> &matrix, bool transpose = false) const {
        GLint location = this->uniformLocation(name);

        if (location >= 0) {
            this->uniform(location, matrix, transpose);
        }
    }

    inline void uniform(const string &name, const Matrix<f32, 3, 3> &matrix, bool transpose = false) const {
        GLint location = this->uniformLocation(name);

        if (location >= 0) {
            this->uniform(location, matrix, transpose);
        }
    }

    inline void uniform(const string &name, const Matrix<f32, 3, 4> &matrix, bool transpose = false) const {
        GLint location = this->uniformLocation(name);

        if (location >= 0) {
            this->uniform(location, matrix, transpose);
        }
    }

    inline void uniform(const string &name, const Matrix<f32, 4, 2> &matrix, bool transpose = false) const {
        GLint location = this->uniformLocation(name);

        if (location >= 0) {
            this->uniform(location, matrix, transpose);
        }
    }

    inline void uniform(const string &name, const Matrix<f32, 4, 3> &matrix, bool transpose = false) const {
        GLint location = this->uniformLocation(name);

        if (location >= 0) {
            this->uniform(location, matrix, transpose);
        }
    }

    inline void uniform(const string &name, const Matrix<f32, 4, 4> &matrix, bool transpose = false) const {
        GLint location = this->uniformLocation(name);

        if (location >= 0) {
            this->uniform(location, matrix, transpose);
        }
    }

    inline void uniform(const string &name, const vector<Matrix<f32, 2, 2> > &values, bool transpose = false) const {
        GLint location = this->uniformLocation(name);

        if (location >= 0) {
            this->uniform(location, values, transpose);
        }
    }

    inline void uniform(const string &name, const vector<Matrix<f32, 2, 3> > &values, bool transpose = false) const {
        GLint location = this->uniformLocation(name);

        if (location >= 0) {
            this->uniform(location, values, transpose);
        }
    }

    inline void uniform(const string &name, const vector<Matrix<f32, 2, 4> > &values, bool transpose = false) const {
        GLint location = this->uniformLocation(name);

        if (location >= 0) {
            this->uniform(location, values, transpose);
        }
    }

    inline void uniform(const string &name, const vector<Matrix<f32, 3, 2> > &values, bool transpose = false) const {
        GLint location = this->uniformLocation(name);

        if (location >= 0) {
            this->uniform(location, values, transpose);
        }
    }

    inline void uniform(const string &name, const vector<Matrix<f32, 3, 3> > &values, bool transpose = false) const {
        GLint location = this->uniformLocation(name);

        if (location >= 0) {
            this->uniform(location, values, transpose);
        }
    }

    inline void uniform(const string &name, const vector<Matrix<f32, 3, 4> > &values, bool transpose = false) const {
        GLint location = this->uniformLocation(name);

        if (location >= 0) {
            this->uniform(location, values, transpose);
        }
    }

    inline void uniform(const string &name, const vector<Matrix<f32, 4, 2> > &values, bool transpose = false) const {
        GLint location = this->uniformLocation(name);

        if (location >= 0) {
            this->uniform(location, values, transpose);
        }
    }

    inline void uniform(const string &name, const vector<Matrix<f32, 4, 3> > &values, bool transpose = false) const {
        GLint location = this->uniformLocation(name);

        if (location >= 0) {
            this->uniform(location, values, transpose);
        }
    }

    inline void uniform(const string &name, const vector<Matrix<f32, 4, 4> > &values, bool transpose = false) const {
        GLint location = this->uniformLocation(name);

        if (location >= 0) {
            this->uniform(location, values, transpose);
        }
    }


    void print() const;
};


#endif //__SHADER_H_INCLUDE__