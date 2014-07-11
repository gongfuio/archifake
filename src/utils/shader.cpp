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


Shader::Shader(i32u type, const std::string &source) : id(GL_ZERO), compiled(false), type(type), source(source) {
    this->id = glCreateShader(type);
    if (this->id == GL_ZERO) {
        return;
    }

    {
        const char *sources[] = {
            source.c_str()
        };
        GLint lengths[] = {
            (GLint)source.length()
        };

        glShaderSource(this->id, 1, sources, lengths);
    }

    glCompileShader(this->id);
    {
        GLint status = GL_FALSE;

        glGetShaderiv(this->id, GL_COMPILE_STATUS, &status);
        if (status) {
            this->compiled = true;
        }
    }
    {
        std::vector<char> buffer;
        GLint length = 0;

        glGetShaderiv(this->id, GL_INFO_LOG_LENGTH, &length);
        buffer.reserve(_max(length, 1));
        glGetShaderInfoLog(this->id, length, &length, buffer.data());
        buffer[length] = '\0';
        this->logs = std::string(buffer.begin(), buffer.begin() + length);
    }
}

Shader::~Shader() {
    glDeleteShader(this->id);
}

bool Shader::isCompiled() const {
    return this->compiled;
}

const std::string & Shader::getLogs() const {
    return this->logs;
}


ShaderProgram::ShaderProgram(const std::list<std::shared_ptr<Shader> > &shaders) {
    this->id = glCreateProgram();
    if (this->id == GL_ZERO) {
        return;
    }

    std::for_each(shaders.begin(), shaders.end(), [&] (const std::shared_ptr<Shader> &shader) {
        if (shader && shader->isCompiled()) {
            glAttachShader(this->id, shader->id);
        }
    });

    glLinkProgram(this->id);
    {
        GLint status = GL_FALSE;

        glGetProgramiv(this->id, GL_LINK_STATUS, &status);
        if (status) {
            this->linked = true;
        }
    }
    {
        std::vector<char> buffer;
        GLint length = 0;

        glGetProgramiv(this->id, GL_INFO_LOG_LENGTH, &length);
        buffer.reserve(_max(length, 1));
        glGetProgramInfoLog(this->id, length, &length, buffer.data());
        buffer[length] = '\0';
        this->linkerLogs = std::string(buffer.begin(), buffer.begin() + length);
    }

    glValidateProgram(this->id);
    {
        GLint status = GL_FALSE;

        glGetProgramiv(this->id, GL_VALIDATE_STATUS, &status);
        if (status) {
            this->validated = true;
        }
    }
    {
        std::vector<char> buffer;
        GLint length = 0;

        glGetProgramiv(this->id, GL_INFO_LOG_LENGTH, &length);
        buffer.reserve(_max(length, 1));
        glGetProgramInfoLog(this->id, length, &length, buffer.data());
        buffer[length] = '\0';
        this->validatorLogs = std::string(buffer.begin(), buffer.begin() + length);
    }

    {
        std::vector<std::string > blockNames;
        std::vector<GLuint> indices;
        std::vector<GLint> blocks;
        std::vector<GLint> offsets;
        std::vector<GLint> arrayStrides;
        std::vector<GLint> matrixStrides;
        std::vector<GLint> rowMajors;
        std::vector<GLint> atomicCounters;
        std::vector<char> buffer;
        GLint count = 0;

        glGetProgramiv(this->id, GL_ACTIVE_UNIFORM_BLOCKS, &count);
        blockNames.reserve(count);
        for (GLint i = 0; i < count; i++) {
            GLint length = 0;
            std::string name;
            GLint size = 0;
            GLint uniforms = 0;
            GLint location = 0;

            glGetProgramiv(this->id, GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH, &length);
            buffer.reserve(_max(length, 1));
            glGetActiveUniformBlockName(this->id, i, length, &length, buffer.data());
            buffer[length] = '\0';
            name = std::string(buffer.begin(), buffer.begin() + length);
            glGetActiveUniformBlockiv(this->id, i, GL_UNIFORM_BLOCK_DATA_SIZE, &size);
            glGetActiveUniformBlockiv(this->id, i, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &uniforms);
            glGetActiveUniformBlockiv(this->id, i, GL_UNIFORM_BLOCK_BINDING, &location);

            blockNames.push_back(name);

            this->uniformBlocks[name] = {
                name,
                location,
                uniforms,
                size
            };
        }
        count = 0;
        glGetProgramiv(this->id, GL_ACTIVE_UNIFORMS, &count);
        indices.reserve(count);
        for (GLint i = 0; i < count; i++) {
            indices[i] = i;
        }
        blocks.reserve(count);
        glGetActiveUniformsiv(this->id, count, indices.data(), GL_UNIFORM_BLOCK_INDEX, blocks.data());
        offsets.reserve(count);
        glGetActiveUniformsiv(this->id, count, indices.data(), GL_UNIFORM_OFFSET, offsets.data());
        arrayStrides.reserve(count);
        glGetActiveUniformsiv(this->id, count, indices.data(), GL_UNIFORM_ARRAY_STRIDE, arrayStrides.data());
        matrixStrides.reserve(count);
        glGetActiveUniformsiv(this->id, count, indices.data(), GL_UNIFORM_MATRIX_STRIDE, matrixStrides.data());
        rowMajors.reserve(count);
        glGetActiveUniformsiv(this->id, count, indices.data(), GL_UNIFORM_IS_ROW_MAJOR, rowMajors.data());
        atomicCounters.reserve(count);
        glGetActiveUniformsiv(this->id, count, indices.data(), GL_UNIFORM_ATOMIC_COUNTER_BUFFER_INDEX, atomicCounters.data());
        for (GLint i = 0; i < count; i++) {
            GLint length = 0;
            std::string name;
            GLint size = 0;
            GLenum type = 0;
            GLint location = 0;
            std::string blockName;

            glGetProgramiv(this->id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &length);
            buffer.reserve(_max(length, 1));
            glGetActiveUniform(this->id, i, length, &length, &size, &type, buffer.data());
            buffer[length] = '\0';
            name = std::string(buffer.begin(), buffer.begin() + length);
            if (blocks[i] >= 0 && blocks[i] < (GLint)blockNames.size()) {
                blockName = blockNames[i];
            }

            this->uniforms[name] = {
                name,
                location,
                type,
                size,
                blockName,
                offsets[i],
                arrayStrides[i],
                matrixStrides[i],
                rowMajors[i] ? true : false
            };
        }
    }

    {
        std::vector<char> buffer;
        GLint count = 0;

        glGetProgramiv(this->id, GL_ACTIVE_ATTRIBUTES, &count);
        for (GLint i = 0; i < count; i++) {
            GLint length = 0;
            std::string name;
            GLint size = 0;
            GLenum type = 0;
            GLint location = 0;

            glGetProgramiv(this->id, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &length);
            buffer.reserve(_max(length, 1));
            glGetActiveAttrib(this->id, i, length, &length, &size, &type, buffer.data());
            buffer[length] = '\0';
            name = std::string(buffer.begin(), buffer.begin() + length);
            location = glGetAttribLocation(this->id, name.c_str());

            this->attributes[name] = {
                name,
                location,
                type,
                size
            };
        }
    }
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(this->id);
}

bool ShaderProgram::isLinked() const {
    return this->linked;
}

bool ShaderProgram::isValidated() const {
    return this->validated;
}

const std::string & ShaderProgram::getLinkerLogs() const {
    return this->linkerLogs;
}

const std::string & ShaderProgram::getValidatorLogs() const {
    return this->validatorLogs;
}

void ShaderProgram::enable() {
    if (this->enabled == 0) {
        glUseProgram(this->id);
    }
    this->enabled++;
}

void ShaderProgram::disable() {
    this->enabled--;
    if (this->enabled == 0) {
        glUseProgram(GL_ZERO);
    }
}

GLint ShaderProgram::uniformLocation(const std::string &name) const {
    auto it = this->uniforms.find(name);

    if (it != this->uniforms.end()) {
        return (*it).second.location;
    }
    return -1;
}

GLint ShaderProgram::attributeLocation(const std::string &name) const {
    auto it = this->attributes.find(name);

    if (it != this->attributes.end()) {
        return (*it).second.location;
    }
    return -1;
}

void ShaderProgram::uniform(GLint location, i32 value) {
    glUniform1i(location, value);
}

void ShaderProgram::uniform(GLint location, const Vector<i32, 2> &vec) {
    glUniform2i(location, vec[0], vec[1]);
}

void ShaderProgram::uniform(GLint location, const Vector<i32, 3> &vec) {
    glUniform3i(location, vec[0], vec[1], vec[2]);
}

void ShaderProgram::uniform(GLint location, const Vector<i32, 4> &vec) {
    glUniform4i(location, vec[0], vec[1], vec[2], vec[3]);
}

void ShaderProgram::uniform(GLint location, const std::vector<i32> &values) {
    glUniform1iv(location, values.size(), values.data());
}

void ShaderProgram::uniform(GLint location, const std::vector<Vector<i32, 2> > &values) {
    vector<i32> buffer(values.size() * 2);

    for (i32u i = 0; i < values.size(); i++) {
        buffer[i * 2 + 0] = values[i][0];
        buffer[i * 2 + 1] = values[i][1];
    }
    glUniform2iv(location, values.size(), buffer.data());
}

void ShaderProgram::uniform(GLint location, const std::vector<Vector<i32, 3> > &values) {
    vector<i32> buffer(values.size() * 3);

    for (i32u i = 0; i < values.size(); i++) {
        buffer[i * 3 + 0] = values[i][0];
        buffer[i * 3 + 1] = values[i][1];
        buffer[i * 3 + 2] = values[i][2];
    }
    glUniform3iv(location, values.size(), buffer.data());
}

void ShaderProgram::uniform(GLint location, const std::vector<Vector<i32, 4> > &values) {
    vector<i32> buffer(values.size() * 4);

    for (i32u i = 0; i < values.size(); i++) {
        buffer[i * 4 + 0] = values[i][0];
        buffer[i * 4 + 1] = values[i][1];
        buffer[i * 4 + 2] = values[i][2];
        buffer[i * 4 + 3] = values[i][3];
    }
    glUniform4iv(location, values.size(), buffer.data());
}

void ShaderProgram::uniform(GLint location, f32 value) {
    glUniform1f(location, value);
}

void ShaderProgram::uniform(GLint location, const Vector<f32, 2> &vec) {
    glUniform2f(location, vec[0], vec[1]);
}

void ShaderProgram::uniform(GLint location, const Vector<f32, 3> &vec) {
    glUniform3f(location, vec[0], vec[1], vec[2]);
}

void ShaderProgram::uniform(GLint location, const Vector<f32, 4> &vec) {
    glUniform4f(location, vec[0], vec[1], vec[2], vec[3]);
}

void ShaderProgram::uniform(GLint location, const std::vector<f32> &values) {
    glUniform1fv(location, values.size(), values.data());
}

void ShaderProgram::uniform(GLint location, const std::vector<Vector<f32, 2> > &values) {
    vector<f32> buffer(values.size() * 2);

    for (i32u i = 0; i < values.size(); i++) {
        buffer[i * 2 + 0] = values[i][0];
        buffer[i * 2 + 1] = values[i][1];
    }
    glUniform2fv(location, values.size(), buffer.data());
}

void ShaderProgram::uniform(GLint location, const std::vector<Vector<f32, 3> > &values) {
    vector<f32> buffer(values.size() * 3);

    for (i32u i = 0; i < values.size(); i++) {
        buffer[i * 3 + 0] = values[i][0];
        buffer[i * 3 + 1] = values[i][1];
        buffer[i * 3 + 2] = values[i][2];
    }
    glUniform3fv(location, values.size(), buffer.data());
}

void ShaderProgram::uniform(GLint location, const std::vector<Vector<f32, 4> > &values) {
    vector<f32> buffer(values.size() * 4);

    for (i32u i = 0; i < values.size(); i++) {
        buffer[i * 4 + 0] = values[i][0];
        buffer[i * 4 + 1] = values[i][1];
        buffer[i * 4 + 2] = values[i][2];
        buffer[i * 4 + 3] = values[i][3];
    }
    glUniform4fv(location, values.size(), buffer.data());
}

void ShaderProgram::uniform(GLint location, const Matrix<f32, 2, 2> &matrix, bool transpose) {
    f32 buffer[] = {
        matrix[0][0], matrix[0][1],
        matrix[1][0], matrix[1][1]
    };

    glUniformMatrix2fv(location, 1, transpose, buffer);
}

void ShaderProgram::uniform(GLint location, const Matrix<f32, 2, 3> &matrix, bool transpose) {
    f32 buffer[] = {
        matrix[0][0], matrix[0][1], matrix[0][2],
        matrix[1][0], matrix[1][1], matrix[1][2]
    };

    glUniformMatrix2x3fv(location, 1, transpose, buffer);
}

void ShaderProgram::uniform(GLint location, const Matrix<f32, 2, 4> &matrix, bool transpose) {
    f32 buffer[] = {
        matrix[0][0], matrix[0][1], matrix[0][2], matrix[0][3],
        matrix[1][0], matrix[1][1], matrix[1][2], matrix[1][3]
    };

    glUniformMatrix2x4fv(location, 1, transpose, buffer);
}

void ShaderProgram::uniform(GLint location, const Matrix<f32, 3, 2> &matrix, bool transpose) {
    f32 buffer[] = {
        matrix[0][0], matrix[0][1],
        matrix[1][0], matrix[1][1],
        matrix[2][0], matrix[2][1]
    };

    glUniformMatrix3x2fv(location, 1, transpose, buffer);
}

void ShaderProgram::uniform(GLint location, const Matrix<f32, 3, 3> &matrix, bool transpose) {
    f32 buffer[] = {
        matrix[0][0], matrix[0][1], matrix[0][2],
        matrix[1][0], matrix[1][1], matrix[1][2],
        matrix[2][0], matrix[2][1], matrix[2][2]
    };

    glUniformMatrix3fv(location, 1, transpose, buffer);
}

void ShaderProgram::uniform(GLint location, const Matrix<f32, 3, 4> &matrix, bool transpose) {
    f32 buffer[] = {
        matrix[0][0], matrix[0][1], matrix[0][2], matrix[0][3],
        matrix[1][0], matrix[1][1], matrix[1][2], matrix[1][3],
        matrix[2][0], matrix[2][1], matrix[2][2], matrix[2][3]
    };

    glUniformMatrix3x4fv(location, 1, transpose, buffer);
}

void ShaderProgram::uniform(GLint location, const Matrix<f32, 4, 2> &matrix, bool transpose) {
    f32 buffer[] = {
        matrix[0][0], matrix[0][1],
        matrix[1][0], matrix[1][1],
        matrix[2][0], matrix[2][1],
        matrix[3][0], matrix[3][1]
    };

    glUniformMatrix4x2fv(location, 1, transpose, buffer);
}

void ShaderProgram::uniform(GLint location, const Matrix<f32, 4, 3> &matrix, bool transpose) {
    f32 buffer[] = {
        matrix[0][0], matrix[0][1], matrix[0][2],
        matrix[1][0], matrix[1][1], matrix[1][2],
        matrix[2][0], matrix[2][1], matrix[2][2],
        matrix[3][0], matrix[3][1], matrix[3][2]
    };

    glUniformMatrix4x3fv(location, 1, transpose, buffer);
}

void ShaderProgram::uniform(GLint location, const Matrix<f32, 4, 4> &matrix, bool transpose) {
    f32 buffer[] = {
        matrix[0][0], matrix[0][1], matrix[0][2], matrix[0][3],
        matrix[1][0], matrix[1][1], matrix[1][2], matrix[1][3],
        matrix[2][0], matrix[2][1], matrix[2][2], matrix[2][3],
        matrix[3][0], matrix[3][1], matrix[3][2], matrix[3][3],
    };

    glUniformMatrix4fv(location, 1, transpose, buffer);
}

void ShaderProgram::uniform(GLint location, const std::vector<Matrix<f32, 2, 2> > &values, bool transpose) {
    vector<f32> buffer(values.size() * 4);

    for (i32u i = 0; i < values.size(); i++) {
        buffer[i * 4 + 0] = values[i][0][0];
        buffer[i * 4 + 1] = values[i][0][1];
        buffer[i * 4 + 2] = values[i][1][0];
        buffer[i * 4 + 3] = values[i][1][1];
    }
    glUniformMatrix2fv(location, values.size(), transpose, buffer.data());
}

void ShaderProgram::uniform(GLint location, const std::vector<Matrix<f32, 2, 3> > &values, bool transpose) {
    vector<f32> buffer(values.size() * 6);

    for (i32u i = 0; i < values.size(); i++) {
        buffer[i * 6 + 0] = values[i][0][0];
        buffer[i * 6 + 1] = values[i][0][1];
        buffer[i * 6 + 2] = values[i][0][2];
        buffer[i * 6 + 3] = values[i][1][0];
        buffer[i * 6 + 4] = values[i][1][1];
        buffer[i * 6 + 5] = values[i][1][2];
    }
    glUniformMatrix2x3fv(location, values.size(), transpose, buffer.data());
}

void ShaderProgram::uniform(GLint location, const std::vector<Matrix<f32, 2, 4> > &values, bool transpose) {
    vector<f32> buffer(values.size() * 8);

    for (i32u i = 0; i < values.size(); i++) {
        buffer[i * 8 + 0] = values[i][0][0];
        buffer[i * 8 + 1] = values[i][0][1];
        buffer[i * 8 + 2] = values[i][0][2];
        buffer[i * 8 + 3] = values[i][0][3];
        buffer[i * 8 + 4] = values[i][1][0];
        buffer[i * 8 + 5] = values[i][1][1];
        buffer[i * 8 + 6] = values[i][1][2];
        buffer[i * 8 + 7] = values[i][1][3];
    }
    glUniformMatrix2x4fv(location, values.size(), transpose, buffer.data());
}

void ShaderProgram::uniform(GLint location, const std::vector<Matrix<f32, 3, 2> > &values, bool transpose) {
    vector<f32> buffer(values.size() * 6);

    for (i32u i = 0; i < values.size(); i++) {
        buffer[i * 6 + 0] = values[i][0][0];
        buffer[i * 6 + 1] = values[i][0][1];
        buffer[i * 6 + 2] = values[i][1][0];
        buffer[i * 6 + 3] = values[i][1][1];
        buffer[i * 6 + 4] = values[i][2][0];
        buffer[i * 6 + 5] = values[i][2][1];
    }
    glUniformMatrix3x2fv(location, values.size(), transpose, buffer.data());
}

void ShaderProgram::uniform(GLint location, const std::vector<Matrix<f32, 3, 3> > &values, bool transpose) {
    vector<f32> buffer(values.size() * 9);

    for (i32u i = 0; i < values.size(); i++) {
        buffer[i * 9 + 0] = values[i][0][0];
        buffer[i * 9 + 1] = values[i][0][1];
        buffer[i * 9 + 2] = values[i][0][2];
        buffer[i * 9 + 3] = values[i][1][0];
        buffer[i * 9 + 4] = values[i][1][1];
        buffer[i * 9 + 5] = values[i][1][2];
        buffer[i * 9 + 6] = values[i][2][0];
        buffer[i * 9 + 7] = values[i][2][1];
        buffer[i * 9 + 8] = values[i][2][2];
    }
    glUniformMatrix3fv(location, values.size(), transpose, buffer.data());
}

void ShaderProgram::uniform(GLint location, const std::vector<Matrix<f32, 3, 4> > &values, bool transpose) {
    vector<f32> buffer(values.size() * 12);

    for (i32u i = 0; i < values.size(); i++) {
        buffer[i * 12 + 0] = values[i][0][0];
        buffer[i * 12 + 1] = values[i][0][1];
        buffer[i * 12 + 2] = values[i][0][2];
        buffer[i * 12 + 3] = values[i][0][3];
        buffer[i * 12 + 4] = values[i][1][0];
        buffer[i * 12 + 5] = values[i][1][1];
        buffer[i * 12 + 6] = values[i][1][2];
        buffer[i * 12 + 7] = values[i][1][3];
        buffer[i * 12 + 8] = values[i][2][0];
        buffer[i * 12 + 9] = values[i][2][1];
        buffer[i * 12 + 10] = values[i][2][2];
        buffer[i * 12 + 11] = values[i][2][3];
    }
    glUniformMatrix3x4fv(location, values.size(), transpose, buffer.data());
}

void ShaderProgram::uniform(GLint location, const std::vector<Matrix<f32, 4, 2> > &values, bool transpose) {
    vector<f32> buffer(values.size() * 8);

    for (i32u i = 0; i < values.size(); i++) {
        buffer[i * 8 + 0] = values[i][0][0];
        buffer[i * 8 + 1] = values[i][0][1];
        buffer[i * 8 + 2] = values[i][1][0];
        buffer[i * 8 + 3] = values[i][1][1];
        buffer[i * 8 + 4] = values[i][2][0];
        buffer[i * 8 + 5] = values[i][2][1];
        buffer[i * 8 + 6] = values[i][3][0];
        buffer[i * 8 + 7] = values[i][3][1];
    }
    glUniformMatrix4x2fv(location, values.size(), transpose, buffer.data());
}

void ShaderProgram::uniform(GLint location, const std::vector<Matrix<f32, 4, 3> > &values, bool transpose) {
    vector<f32> buffer(values.size() * 12);

    for (i32u i = 0; i < values.size(); i++) {
        buffer[i * 12 + 0] = values[i][0][0];
        buffer[i * 12 + 1] = values[i][0][1];
        buffer[i * 12 + 2] = values[i][0][2];
        buffer[i * 12 + 3] = values[i][1][0];
        buffer[i * 12 + 4] = values[i][1][1];
        buffer[i * 12 + 5] = values[i][1][2];
        buffer[i * 12 + 6] = values[i][2][0];
        buffer[i * 12 + 7] = values[i][2][1];
        buffer[i * 12 + 8] = values[i][2][2];
        buffer[i * 12 + 9] = values[i][3][0];
        buffer[i * 12 + 10] = values[i][3][1];
        buffer[i * 12 + 11] = values[i][3][2];
    }
    glUniformMatrix4x3fv(location, values.size(), transpose, buffer.data());
}

void ShaderProgram::uniform(GLint location, const std::vector<Matrix<f32, 4, 4> > &values, bool transpose) {
    vector<f32> buffer(values.size() * 16);

    for (i32u i = 0; i < values.size(); i++) {
        buffer[i * 16 + 0] = values[i][0][0];
        buffer[i * 16 + 1] = values[i][0][1];
        buffer[i * 16 + 2] = values[i][0][2];
        buffer[i * 16 + 3] = values[i][0][3];
        buffer[i * 16 + 4] = values[i][1][0];
        buffer[i * 16 + 5] = values[i][1][1];
        buffer[i * 16 + 6] = values[i][1][2];
        buffer[i * 16 + 7] = values[i][1][3];
        buffer[i * 16 + 8] = values[i][2][0];
        buffer[i * 16 + 9] = values[i][2][1];
        buffer[i * 16 + 10] = values[i][2][2];
        buffer[i * 16 + 11] = values[i][2][3];
        buffer[i * 16 + 12] = values[i][3][0];
        buffer[i * 16 + 13] = values[i][3][1];
        buffer[i * 16 + 14] = values[i][3][2];
        buffer[i * 16 + 15] = values[i][3][3];
    }
    glUniformMatrix4x3fv(location, values.size(), transpose, buffer.data());
}
