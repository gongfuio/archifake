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


static const char * getGLTypeName(GLint type) {
    switch (type) {
    case GL_BOOL:
        return "bool";
    case GL_BOOL_VEC2:
        return "bool[2]";
    case GL_BOOL_VEC3:
        return "bool[3]";
    case GL_BOOL_VEC4:
        return "bool[4]";

    case GL_INT:
        return "i32";
    case GL_INT_VEC2:
        return "i32[2]";
    case GL_INT_VEC3:
        return "i32[3]";
    case GL_INT_VEC4:
        return "i32[4]";

    case GL_UNSIGNED_INT:
        return "i32u";
    case GL_UNSIGNED_INT_VEC2:
        return "i32u[2]";
    case GL_UNSIGNED_INT_VEC3:
        return "i32u[3]";
    case GL_UNSIGNED_INT_VEC4:
        return "i32u[4]";

    case GL_UNSIGNED_INT_ATOMIC_COUNTER:
        return "atomiccounter[i32u]";

    case GL_FLOAT:
        return "f32";
    case GL_FLOAT_VEC2:
        return "f32[2]";
    case GL_FLOAT_VEC3:
        return "f32[3]";
    case GL_FLOAT_VEC4:
        return "f32[4]";
    case GL_FLOAT_MAT2:
        return "f32[2][2]";
    case GL_FLOAT_MAT2x3:
        return "f32[2][3]";
    case GL_FLOAT_MAT2x4:
        return "f32[2][4]";
    case GL_FLOAT_MAT3x2:
        return "f32[3][2]";
    case GL_FLOAT_MAT3:
        return "f32[3][3]";
    case GL_FLOAT_MAT3x4:
        return "f32[3][4]";
    case GL_FLOAT_MAT4x2:
        return "f32[4][2]";
    case GL_FLOAT_MAT4x3:
        return "f32[4][3]";
    case GL_FLOAT_MAT4:
        return "f32[4][4]";

    case GL_DOUBLE:
        return "f64";
    case GL_DOUBLE_VEC2:
        return "f64[2]";
    case GL_DOUBLE_VEC3:
        return "f64[3]";
    case GL_DOUBLE_VEC4:
        return "f64[4]";
    case GL_DOUBLE_MAT2:
        return "f64[2][2]";
    case GL_DOUBLE_MAT2x3:
        return "f64[2][3]";
    case GL_DOUBLE_MAT2x4:
        return "f64[2][4]";
    case GL_DOUBLE_MAT3x2:
        return "f64[3][2]";
    case GL_DOUBLE_MAT3:
        return "f64[3][3]";
    case GL_DOUBLE_MAT3x4:
        return "f64[3][4]";
    case GL_DOUBLE_MAT4x2:
        return "f64[4][2]";
    case GL_DOUBLE_MAT4x3:
        return "f64[4][3]";
    case GL_DOUBLE_MAT4:
        return "f64[4][4]";

//  case GL_INT_SAMPLER_1D:
//  case GL_INT_SAMPLER_1D_ARRAY:
    case GL_INT_SAMPLER_2D:
        return "sampler2d[i32]";
    case GL_INT_SAMPLER_2D_ARRAY:
        return "sampler2darray[i32]";
//  case GL_INT_SAMPLER_2D_RECT:
//  case GL_INT_SAMPLER_2D_MULTISAMPLE:
//  case GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY:
    case GL_INT_SAMPLER_3D:
        return "sampler3d[i32]";
    case GL_INT_SAMPLER_CUBE:
        return "samplercube[i32]";
//  case GL_INT_SAMPLER_CUBE_MAP_ARRAY:
//  case GL_INT_SAMPLER_BUFFER:

//  case GL_INT_IMAGE_1D:
//  case GL_INT_IMAGE_1D_ARRAY:
    case GL_INT_IMAGE_2D:
        return "image2d[i32]";
    case GL_INT_IMAGE_2D_ARRAY:
        return "image2darray[i32]";
//  case GL_INT_IMAGE_2D_RECT:
//  case GL_INT_IMAGE_2D_MULTISAMPLE:
//  case GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY:
    case GL_INT_IMAGE_3D:
        return "image3d[i32]";
    case GL_INT_IMAGE_CUBE:
        return "imagecube[i32]";
//  case GL_INT_IMAGE_CUBE_MAP_ARRAY:
//  case GL_INT_IMAGE_BUFFER:

//  case GL_UNSIGNED_INT_SAMPLER_1D:
//  case GL_UNSIGNED_INT_SAMPLER_1D_ARRAY:
    case GL_UNSIGNED_INT_SAMPLER_2D:
        return "sampler2d[i32u]";
    case GL_UNSIGNED_INT_SAMPLER_2D_ARRAY:
        return "sampler2darray[i32u]";
//  case GL_UNSIGNED_INT_SAMPLER_2D_RECT:
//  case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE:
//  case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY:
    case GL_UNSIGNED_INT_SAMPLER_3D:
        return "sampler3d[i32u]";
    case GL_UNSIGNED_INT_SAMPLER_CUBE:
        return "samplercube[i32u]";
//  case GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY:
//  case GL_UNSIGNED_INT_SAMPLER_BUFFER:

//  case GL_UNSIGNED_INT_IMAGE_1D:
//  case GL_UNSIGNED_INT_IMAGE_1D_ARRAY:
    case GL_UNSIGNED_INT_IMAGE_2D:
        return "image2d[i32u]";
    case GL_UNSIGNED_INT_IMAGE_2D_ARRAY:
        return "image2darray[i32u]";
//  case GL_UNSIGNED_INT_IMAGE_2D_RECT:
//  case GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE:
//  case GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY:
    case GL_UNSIGNED_INT_IMAGE_3D:
        return "image3d[i32u]";
    case GL_UNSIGNED_INT_IMAGE_CUBE:
        return "imagecube[i32u]";
//  case GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY:
//  case GL_UNSIGNED_INT_IMAGE_BUFFER:

//  case GL_SAMPLER_1D:
//  case GL_SAMPLER_1D_ARRAY:
//  case GL_SAMPLER_1D_ARRAY_SHADOW:
//  case GL_SAMPLER_1D_SHADOW:
    case GL_SAMPLER_2D:
        return "sampler2d[f32]";
    case GL_SAMPLER_2D_ARRAY:
        return "sampler2darray[f32]";
    case GL_SAMPLER_2D_ARRAY_SHADOW:
        return "sampler2darrayshadow[f32]";
//  case GL_SAMPLER_2D_RECT:
//  case GL_SAMPLER_2D_RECT_SHADOW:
    case GL_SAMPLER_2D_SHADOW:
        return "sampler2dshadow[f32]";
//  case GL_SAMPLER_2D_MULTISAMPLE:
//  case GL_SAMPLER_2D_MULTISAMPLE_ARRAY:
    case GL_SAMPLER_3D:
        return "sampler3d[f32]";
    case GL_SAMPLER_CUBE:
        return "samplercube[f32]";
//  case GL_SAMPLER_CUBE_MAP_ARRAY:
//  case GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW:
    case GL_SAMPLER_CUBE_SHADOW:
        return "samplercubeshadow[f32]";
//  case GL_SAMPLER_BUFFER:

//  case GL_IMAGE_1D:
//  case GL_IMAGE_1D_ARRAY:
    case GL_IMAGE_2D:
        return "image2d[f32]";
    case GL_IMAGE_2D_ARRAY:
        return "image2darray[f32]";
//  case GL_IMAGE_2D_RECT:
//  case GL_IMAGE_2D_MULTISAMPLE:
//  case GL_IMAGE_2D_MULTISAMPLE_ARRAY:
    case GL_IMAGE_3D:
        return "image3d[f32]";
    case GL_IMAGE_CUBE:
        return "imagecube[f32]";
//  case GL_IMAGE_CUBE_MAP_ARRAY:
//  case GL_IMAGE_BUFFER:
    }
    return "unknown";
}


Shader::Shader(GLenum type, const string &source) : id(GL_ZERO), compiled(false), type(type), source(source) {
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
        vector<char> buffer;
        GLint length = 0;

        glGetShaderiv(this->id, GL_INFO_LOG_LENGTH, &length);
        buffer.reserve(_max(length, 1));
        glGetShaderInfoLog(this->id, length, &length, buffer.data());
        buffer[length] = '\0';
        this->logs = string(buffer.begin(), buffer.begin() + length);
    }
}

Shader::~Shader() {
    if (this->id != GL_ZERO) {
        glDeleteShader(this->id);
    }
}

bool Shader::isCompiled() const {
    return this->compiled;
}

const string & Shader::getLogs() const {
    return this->logs;
}


shared_ptr<Shader> Shader::fromFile(GLenum type, const string &path) {
    stringstream source;
    ifstream file(path);

    while (!file.eof()) {
        source.put(file.get());
    }
    return shared_ptr<Shader>(new Shader(type, source.str()));
}


const ShaderProgram::UniformBlock ShaderProgram::emptyUniformBlock = {
    "",
    -1,
    0,
    0
};

const ShaderProgram::Uniform ShaderProgram::emptyUniform = {
    "",
    -1,
    GL_ZERO,
    0,
    "",
    0,
    0,
    0,
    false
};

const ShaderProgram::Attribute ShaderProgram::emptyAttribute = {
    "",
    -1,
    GL_ZERO,
    0
};


ShaderProgram::ShaderProgram(const shared_ptr<Shader> &vertexShader, const shared_ptr<Shader> &fragmentShader) : id(GL_ZERO), linked(false), validated(false), enabled(0) {
    this->shaders.push_back(vertexShader);
    this->shaders.push_back(fragmentShader);
    this->link();
}

ShaderProgram::ShaderProgram(const list<shared_ptr<Shader> > &shaders) : id(GL_ZERO), linked(false), validated(false), enabled(0), shaders(shaders) {
    this->link();
}

ShaderProgram::~ShaderProgram() {
    if (this->id != GL_ZERO) {
        glDeleteProgram(this->id);
    }
}

void ShaderProgram::link() {
    this->id = glCreateProgram();
    if (this->id == GL_ZERO) {
        return;
    }

    for_each(this->shaders.begin(), this->shaders.end(), [this] (const shared_ptr<Shader> &shader) {
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
        vector<char> buffer;
        GLint length = 0;

        glGetProgramiv(this->id, GL_INFO_LOG_LENGTH, &length);
        buffer.reserve(_max(length, 1));
        glGetProgramInfoLog(this->id, length, &length, buffer.data());
        buffer[length] = '\0';
        this->linkerLogs = string(buffer.begin(), buffer.begin() + length);
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
        vector<char> buffer;
        GLint length = 0;

        glGetProgramiv(this->id, GL_INFO_LOG_LENGTH, &length);
        buffer.reserve(_max(length, 1));
        glGetProgramInfoLog(this->id, length, &length, buffer.data());
        buffer[length] = '\0';
        this->validatorLogs = string(buffer.begin(), buffer.begin() + length);
    }

    {
        vector<string > blockNames;
        vector<GLuint> indices;
        vector<GLint> blocks;
        vector<GLint> offsets;
        vector<GLint> arrayStrides;
        vector<GLint> matrixStrides;
        vector<GLint> rowMajors;
        vector<GLint> atomicCounters;
        vector<char> buffer;
        GLint count = 0;

        glGetProgramiv(this->id, GL_ACTIVE_UNIFORM_BLOCKS, &count);
        blockNames.reserve(count);
        for (GLint i = 0; i < count; i++) {
            GLint length = 0;
            string name;
            GLint size = 0;
            GLint uniforms = 0;
            GLint location = 0;

            glGetProgramiv(this->id, GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH, &length);
            buffer.reserve(_max(length, 1));
            glGetActiveUniformBlockName(this->id, i, length, &length, buffer.data());
            buffer[length] = '\0';
            name = string(buffer.begin(), buffer.begin() + length);
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
            string name;
            GLint size = 0;
            GLenum type = 0;
            GLint location = 0;
            string blockName;

            glGetProgramiv(this->id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &length);
            buffer.reserve(_max(length, 1));
            glGetActiveUniform(this->id, i, length, &length, &size, &type, buffer.data());
            buffer[length] = '\0';
            name = string(buffer.begin(), buffer.begin() + length);
            if (blocks[i] >= 0 && blocks[i] < (GLint)blockNames.size()) {
                blockName = blockNames[i];
            }
            location = glGetUniformLocation(this->id, name.c_str());

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
        vector<char> buffer;
        GLint count = 0;

        glGetProgramiv(this->id, GL_ACTIVE_ATTRIBUTES, &count);
        for (GLint i = 0; i < count; i++) {
            GLint length = 0;
            string name;
            GLint size = 0;
            GLenum type = 0;
            GLint location = 0;

            glGetProgramiv(this->id, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &length);
            buffer.reserve(_max(length, 1));
            glGetActiveAttrib(this->id, i, length, &length, &size, &type, buffer.data());
            buffer[length] = '\0';
            name = string(buffer.begin(), buffer.begin() + length);
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

bool ShaderProgram::isLinked() const {
    return this->linked;
}

bool ShaderProgram::isValidated() const {
    return this->validated;
}

const string & ShaderProgram::getLinkerLogs() const {
    return this->linkerLogs;
}

const string & ShaderProgram::getValidatorLogs() const {
    return this->validatorLogs;
}

void ShaderProgram::enable() {
    if (this->enabled == 0) {
        if (this->id == GL_ZERO) {
            return;
        }
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

set<string> ShaderProgram::uniformBlockNames() const {
    return set<string>(
        map_key_const_iterator<map<string, UniformBlock> >(this->uniformBlocks.begin()),
        map_key_const_iterator<map<string, UniformBlock> >(this->uniformBlocks.end())
    );
}

set<string> ShaderProgram::uniformNames() const {
    return set<string>(
        map_key_const_iterator<map<string, Uniform> >(this->uniforms.begin()),
        map_key_const_iterator<map<string, Uniform> >(this->uniforms.end())
    );
}

set<string> ShaderProgram::attributeNames() const {
    return set<string>(
        map_key_const_iterator<map<string, Attribute> >(this->attributes.begin()),
        map_key_const_iterator<map<string, Attribute> >(this->attributes.end())
    );
}

const ShaderProgram::UniformBlock & ShaderProgram::uniformBlock(const string &name) const {
    auto it = this->uniformBlocks.find(name);

    if (it != this->uniformBlocks.end()) {
        return (*it).second;
    }
    return ShaderProgram::emptyUniformBlock;
}

const ShaderProgram::Uniform & ShaderProgram::uniform(const string &name) const {
    auto it = this->uniforms.find(name);

    if (it != this->uniforms.end()) {
        return (*it).second;
    }
    return ShaderProgram::emptyUniform;
}

const ShaderProgram::Attribute & ShaderProgram::attribute(const string &name) const {
    auto it = this->attributes.find(name);

    if (it != this->attributes.end()) {
        return (*it).second;
    }
    return ShaderProgram::emptyAttribute;
}

GLint ShaderProgram::uniformBlockLocation(const string &name) const {
    return this->uniformBlock(name).location;
}

GLint ShaderProgram::uniformLocation(const string &name) const {
    return this->uniform(name).location;
}

GLint ShaderProgram::attributeLocation(const string &name) const {
    return this->attribute(name).location;
}

void ShaderProgram::uniform(GLint location, i32 value) const {
    glUniform1i(location, value);
}

void ShaderProgram::uniform(GLint location, const Vector<i32, 2> &vec) const {
    glUniform2i(location, vec[0], vec[1]);
}

void ShaderProgram::uniform(GLint location, const Vector<i32, 3> &vec) const {
    glUniform3i(location, vec[0], vec[1], vec[2]);
}

void ShaderProgram::uniform(GLint location, const Vector<i32, 4> &vec) const {
    glUniform4i(location, vec[0], vec[1], vec[2], vec[3]);
}

void ShaderProgram::uniform(GLint location, const vector<i32> &values) const {
    glUniform1iv(location, values.size(), values.data());
}

void ShaderProgram::uniform(GLint location, const vector<Vector<i32, 2> > &values) const {
    vector<i32> buffer(values.size() * 2);

    for (i32u i = 0; i < values.size(); i++) {
        buffer[i * 2 + 0] = values[i][0];
        buffer[i * 2 + 1] = values[i][1];
    }
    glUniform2iv(location, values.size(), buffer.data());
}

void ShaderProgram::uniform(GLint location, const vector<Vector<i32, 3> > &values) const {
    vector<i32> buffer(values.size() * 3);

    for (i32u i = 0; i < values.size(); i++) {
        buffer[i * 3 + 0] = values[i][0];
        buffer[i * 3 + 1] = values[i][1];
        buffer[i * 3 + 2] = values[i][2];
    }
    glUniform3iv(location, values.size(), buffer.data());
}

void ShaderProgram::uniform(GLint location, const vector<Vector<i32, 4> > &values) const {
    vector<i32> buffer(values.size() * 4);

    for (i32u i = 0; i < values.size(); i++) {
        buffer[i * 4 + 0] = values[i][0];
        buffer[i * 4 + 1] = values[i][1];
        buffer[i * 4 + 2] = values[i][2];
        buffer[i * 4 + 3] = values[i][3];
    }
    glUniform4iv(location, values.size(), buffer.data());
}

void ShaderProgram::uniform(GLint location, f32 value) const {
    glUniform1f(location, value);
}

void ShaderProgram::uniform(GLint location, const Vector<f32, 2> &vec) const {
    glUniform2f(location, vec[0], vec[1]);
}

void ShaderProgram::uniform(GLint location, const Vector<f32, 3> &vec) const {
    glUniform3f(location, vec[0], vec[1], vec[2]);
}

void ShaderProgram::uniform(GLint location, const Vector<f32, 4> &vec) const {
    glUniform4f(location, vec[0], vec[1], vec[2], vec[3]);
}

void ShaderProgram::uniform(GLint location, const vector<f32> &values) const {
    glUniform1fv(location, values.size(), values.data());
}

void ShaderProgram::uniform(GLint location, const vector<Vector<f32, 2> > &values) const {
    vector<f32> buffer(values.size() * 2);
    f32 *ptr = buffer.data();

    for (i32u i = 0; i < values.size(); i++) {
        values[i].copy(ptr);
        ptr += 2;
    }
    glUniform2fv(location, values.size(), buffer.data());
}

void ShaderProgram::uniform(GLint location, const vector<Vector<f32, 3> > &values) const {
    vector<f32> buffer(values.size() * 3);
    f32 *ptr = buffer.data();

    for (i32u i = 0; i < values.size(); i++) {
        values[i].copy(ptr);
        ptr += 3;
    }
    glUniform3fv(location, values.size(), buffer.data());
}

void ShaderProgram::uniform(GLint location, const vector<Vector<f32, 4> > &values) const {
    vector<f32> buffer(values.size() * 4);
    f32 *ptr = buffer.data();

    for (i32u i = 0; i < values.size(); i++) {
        values[i].copy(ptr);
        ptr += 4;
    }
    glUniform4fv(location, values.size(), buffer.data());
}

void ShaderProgram::uniform(GLint location, const Matrix<f32, 2, 2> &matrix, bool transpose) const {
    f32 buffer[4];

    matrix.copyTransposed(buffer);
    glUniformMatrix2fv(location, 1, transpose, buffer);
}

void ShaderProgram::uniform(GLint location, const Matrix<f32, 2, 3> &matrix, bool transpose) const {
    f32 buffer[6];

    matrix.copyTransposed(buffer);
    glUniformMatrix2x3fv(location, 1, transpose, buffer);
}

void ShaderProgram::uniform(GLint location, const Matrix<f32, 2, 4> &matrix, bool transpose) const {
    f32 buffer[8];

    matrix.copyTransposed(buffer);
    glUniformMatrix2x4fv(location, 1, transpose, buffer);
}

void ShaderProgram::uniform(GLint location, const Matrix<f32, 3, 2> &matrix, bool transpose) const {
    f32 buffer[6];

    matrix.copyTransposed(buffer);
    glUniformMatrix3x2fv(location, 1, transpose, buffer);
}

void ShaderProgram::uniform(GLint location, const Matrix<f32, 3, 3> &matrix, bool transpose) const {
    f32 buffer[9];

    matrix.copyTransposed(buffer);
    glUniformMatrix3fv(location, 1, transpose, buffer);
}

void ShaderProgram::uniform(GLint location, const Matrix<f32, 3, 4> &matrix, bool transpose) const {
    f32 buffer[12];

    matrix.copyTransposed(buffer);
    glUniformMatrix3x4fv(location, 1, transpose, buffer);
}

void ShaderProgram::uniform(GLint location, const Matrix<f32, 4, 2> &matrix, bool transpose) const {
    f32 buffer[8];

    matrix.copyTransposed(buffer);
    glUniformMatrix4x2fv(location, 1, transpose, buffer);
}

void ShaderProgram::uniform(GLint location, const Matrix<f32, 4, 3> &matrix, bool transpose) const {
    f32 buffer[12];

    matrix.copyTransposed(buffer);
    glUniformMatrix4x3fv(location, 1, transpose, buffer);
}

void ShaderProgram::uniform(GLint location, const Matrix<f32, 4, 4> &matrix, bool transpose) const {
    f32 buffer[16];

    matrix.copyTransposed(buffer);
    glUniformMatrix4fv(location, 1, transpose, buffer);
}

void ShaderProgram::uniform(GLint location, const vector<Matrix<f32, 2, 2> > &values, bool transpose) const {
    vector<f32> buffer(values.size() * 4);
    f32 *ptr = buffer.data();

    for (i32u i = 0; i < values.size(); i++) {
        values[i].copyTransposed(ptr);
        ptr += 4;
    }
    glUniformMatrix2fv(location, values.size(), transpose, buffer.data());
}

void ShaderProgram::uniform(GLint location, const vector<Matrix<f32, 2, 3> > &values, bool transpose) const {
    vector<f32> buffer(values.size() * 6);
    f32 *ptr = buffer.data();

    for (i32u i = 0; i < values.size(); i++) {
        values[i].copyTransposed(ptr);
        ptr += 6;
    }
    glUniformMatrix2x3fv(location, values.size(), transpose, buffer.data());
}

void ShaderProgram::uniform(GLint location, const vector<Matrix<f32, 2, 4> > &values, bool transpose) const {
    vector<f32> buffer(values.size() * 8);
    f32 *ptr = buffer.data();

    for (i32u i = 0; i < values.size(); i++) {
        values[i].copyTransposed(ptr);
        ptr += 8;
    }
    glUniformMatrix2x4fv(location, values.size(), transpose, buffer.data());
}

void ShaderProgram::uniform(GLint location, const vector<Matrix<f32, 3, 2> > &values, bool transpose) const {
    vector<f32> buffer(values.size() * 6);
    f32 *ptr = buffer.data();

    for (i32u i = 0; i < values.size(); i++) {
        values[i].copyTransposed(ptr);
        ptr += 6;
    }
    glUniformMatrix3x2fv(location, values.size(), transpose, buffer.data());
}

void ShaderProgram::uniform(GLint location, const vector<Matrix<f32, 3, 3> > &values, bool transpose) const {
    vector<f32> buffer(values.size() * 9);
    f32 *ptr = buffer.data();

    for (i32u i = 0; i < values.size(); i++) {
        values[i].copyTransposed(ptr);
        ptr += 9;
    }
    glUniformMatrix3fv(location, values.size(), transpose, buffer.data());
}

void ShaderProgram::uniform(GLint location, const vector<Matrix<f32, 3, 4> > &values, bool transpose) const {
    vector<f32> buffer(values.size() * 12);
    f32 *ptr = buffer.data();

    for (i32u i = 0; i < values.size(); i++) {
        values[i].copyTransposed(ptr);
        ptr += 12;
    }
    glUniformMatrix3x4fv(location, values.size(), transpose, buffer.data());
}

void ShaderProgram::uniform(GLint location, const vector<Matrix<f32, 4, 2> > &values, bool transpose) const {
    vector<f32> buffer(values.size() * 8);
    f32 *ptr = buffer.data();

    for (i32u i = 0; i < values.size(); i++) {
        values[i].copyTransposed(ptr);
        ptr += 8;
    }
    glUniformMatrix4x2fv(location, values.size(), transpose, buffer.data());
}

void ShaderProgram::uniform(GLint location, const vector<Matrix<f32, 4, 3> > &values, bool transpose) const {
    vector<f32> buffer(values.size() * 12);
    f32 *ptr = buffer.data();

    for (i32u i = 0; i < values.size(); i++) {
        values[i].copyTransposed(ptr);
        ptr += 12;
    }
    glUniformMatrix4x3fv(location, values.size(), transpose, buffer.data());
}

void ShaderProgram::uniform(GLint location, const vector<Matrix<f32, 4, 4> > &values, bool transpose) const {
    vector<f32> buffer(values.size() * 16);
    f32 *ptr = buffer.data();

    for (i32u i = 0; i < values.size(); i++) {
        values[i].copyTransposed(ptr);
        ptr += 16;
    }
    glUniformMatrix4x3fv(location, values.size(), transpose, buffer.data());
}

void ShaderProgram::print() const {
    auto bNames(this->uniformBlockNames());
    auto uNames(this->uniformNames());
    auto aNames(this->attributeNames());

    printf("program\n");
    for_each(this->shaders.begin(), this->shaders.end(), [this] (const shared_ptr<Shader> &shader) {
        if (shader && shader->getLogs().length() > 0) {
            printf("logs(shader): %s\n", shader->getLogs().c_str());
        }
    });
    if (this->getLinkerLogs().length() > 0) {
        printf("logs(linker): %s\n", this->getLinkerLogs().c_str());
    }
    if (this->getValidatorLogs().length() > 0) {
        printf("logs(validator): %s\n", this->getValidatorLogs().c_str());
    }

    for_each(bNames.begin(), bNames.end(), [this] (const string &name) {
        auto block(this->uniformBlock(name));

        printf("block[%s]\n", block.name.c_str());
        printf(" location: %d\n", block.location);
        printf(" uniforms: %d\n", block.uniforms);
        printf(" size: %d\n", block.size);
    });
    for_each(uNames.begin(), uNames.end(), [this] (const string &name) {
        auto uniform(this->uniform(name));

        printf("uniform[%s]\n", uniform.name.c_str());
        printf(" location: %d\n", uniform.location);
        printf(" type: %s\n", getGLTypeName(uniform.type));
        printf(" size: %d\n", uniform.size);
        if (uniform.blockName.length() > 0) {
            printf(" block: %s\n", uniform.blockName.c_str());
            printf(" offset: %d\n", uniform.blockOffset);
            printf(" arrayStride: %d\n", uniform.arrayStride);
            printf(" matrixStride: %d\n", uniform.matrixStride);
            printf(" rowMajor: %s\n", uniform.rowMajor ? "true" : "false");
        }
    });
    for_each(aNames.begin(), aNames.end(), [this] (const string &name) {
        auto attribute(this->attribute(name));

        printf("attribute[%s]\n", attribute.name.c_str());
        printf(" location: %d\n", attribute.location);
        printf(" type: %s\n", getGLTypeName(attribute.type));
        printf(" size: %d\n", attribute.size);
    });
}
