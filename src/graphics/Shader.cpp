//
// Created by korikmat on 27.02.2024.
//

#include "Shader.h"

#define GLEW_STATIC

#include <GL/glew.h>

#include <iostream>
#include <vector>

Shader::Shader(const char *vertex_path, const char *fragment_path) {
    this->id = loadShader(vertex_path, fragment_path);
    if (this->id == 0) {
        std::cerr << "Failed to create program." << std::endl;
        throw std::exception();
    }
}

Shader::Shader(const char *vertex_path, const char *fragment_path, const char *geometry_path) {
    this->id = loadShader(vertex_path, fragment_path, geometry_path);
    if (this->id == 0) {
        std::cerr << "Failed to create program." << std::endl;
        throw std::exception();
    }
}

Shader::~Shader() {
    glDeleteProgram(id);
}

void Shader::use() {
    glUseProgram(id);
}

void Shader::uniformMatrix(const char *name, glm::mat4 matrix) {
    int location = glGetUniformLocation(id, name);
    glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

void Shader::uniformMat3(const char *name, glm::mat3 matrix) {
    int location = glGetUniformLocation(id, name);
    glUniformMatrix3fv(location, 1, GL_FALSE, &matrix[0][0]);
}

void Shader::uniformBool(const char *name, bool value) {
    int location = glGetUniformLocation(id, name);
    if (value)
        glUniform1i(location, GL_TRUE);
    else
        glUniform1i(location, GL_FALSE);
}

void Shader::uniformInt(const char *name, int value) {
    int location = glGetUniformLocation(id, name);
    glUniform1i(location, value);
}


void Shader::uniformVec2(const char *name, glm::vec2 vec) {
    int location = glGetUniformLocation(id, name);
    glUniform2fv(location, 1, &vec[0]);
}

void Shader::uniformVec3(const char *name, glm::vec3 vec) {
    int location = glGetUniformLocation(id, name);
    glUniform3fv(location, 1, &vec[0]);
}

void Shader::uniformVec4(const char *name, glm::vec4 vec) {
    int location = glGetUniformLocation(id, name);
    glUniform4fv(location, 1, &vec[0]);
}

void Shader::uniformFloat(const char *name, float value) {
    int location = glGetUniformLocation(id, name);
    glUniform1f(location, value);
}

#define CHECK_GL_ERROR() do { checkGLError(__FUNCTION__, __LINE__); } while(0)

void checkGLError(const char *where, int line) {
    GLenum err = glGetError();
    if (err == GL_NONE)
        return;

    std::string errString = "<unknown>";
    switch (err) {
        case GL_INVALID_ENUM:
            errString = "GL_INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            errString = "GL_INVALID_VALUE";
            break;
        case GL_INVALID_OPERATION:
            errString = "GL_INVALID_OPERATION";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            errString = "GL_INVALID_FRAMEBUFFER_OPERATION";
            break;
        case GL_OUT_OF_MEMORY:
            errString = "GL_OUT_OF_MEMORY";
            break;
        default:;
    }
    if (where == nullptr || *where == 0)
        std::cerr << "GL error occurred: " << errString << std::endl;
    else
        std::cerr << "GL error occurred in " << where << ":" << line << ": " << errString << std::endl;
}

bool linkProgram(GLuint program) {
    glLinkProgram(program);

    GLint status = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    CHECK_GL_ERROR();

    if (status == GL_FALSE) {
        GLint infoLogLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

        GLchar strInfoLog[infoLogLength + 1];
        glGetProgramInfoLog(program, infoLogLength, nullptr, strInfoLog);
        std::cerr << "Linker failure: " << strInfoLog << std::endl;

        return false;
    }

    return true;
}

void deleteProgramAndShaders(GLuint program) {
    const GLsizei MAX_COUNT = 10;  // Pisvejc's constant
    GLsizei count = 0;
    GLuint shaders[MAX_COUNT];

    if (program != 0) {
        glGetAttachedShaders(program, MAX_COUNT, &count, shaders);
        for (int i = 0; i < count; i++)
            glDeleteShader(shaders[i]);

        glDeleteProgram(program);
    }
}

GLuint createProgram(const GLuint *shaders) {
    GLuint program = glCreateProgram();

    auto *shaders_tmp = (GLuint *) shaders;
    while (shaders_tmp && *shaders_tmp)
        glAttachShader(program, *shaders_tmp++);
    CHECK_GL_ERROR();

    if (!linkProgram(program)) {
        deleteProgramAndShaders(program);
        return 0;
    }
    while (shaders && *shaders)
        glDeleteShader(*shaders++);
    CHECK_GL_ERROR();

    return program;
}

GLuint createShaderFromSource(GLenum eShaderType, const char *strFileData) {
    GLuint shader = glCreateShader(eShaderType);
    glShaderSource(shader, 1, &strFileData, nullptr);

    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

        GLchar strInfoLog[infoLogLength + 1];
        glGetShaderInfoLog(shader, infoLogLength, nullptr, strInfoLog);

        const char *strShaderType = nullptr;
        switch (eShaderType) {
            case GL_VERTEX_SHADER:
                strShaderType = "vertex";
                break;
            case GL_FRAGMENT_SHADER:
                strShaderType = "fragment";
                break;
            case GL_GEOMETRY_SHADER:
                strShaderType = "geometry";
                break;
        }

        std::cerr << "Compile failure in " << strShaderType << " shader:" << std::endl;
        std::cerr << strInfoLog;

        glDeleteShader(shader);
        return 0;
    }

    CHECK_GL_ERROR();
    return shader;
}

GLuint createShaderFromFile(GLenum eShaderType, const char *filename) {
    FILE *f = fopen(filename, "rb");
    if (!f) {
        std::cerr << "Unable to open file " << filename << " for reading." << std::endl;
        return 0;
    } else
        std::cout << "loading shader: " << filename << std::endl;

    fseek(f, 0, SEEK_END);
    int length = ftell(f);
    fseek(f, 0, SEEK_SET);

    char buffer[length + 1];
    int length_tmp = fread(buffer, 1, length, f);
    if (length_tmp != length) {
        std::cerr << "Error reading from file. Lengths are not equal." << filename << std::endl;
        fclose(f);
        return 0;
    }
    fclose(f);
    buffer[length] = '\0';

    GLuint sh = createShaderFromSource(eShaderType, buffer);
    return sh;
}

unsigned int Shader::loadShader(const char *vertex_path, const char *fragment_path) {
    GLuint vertexShader = createShaderFromFile(GL_VERTEX_SHADER, vertex_path);
    if (vertexShader == 0) {
        std::cerr << "Failed to load vertex shader " << vertex_path << " ." << std::endl;
        return 0;
    }
    GLuint fragmentShader = createShaderFromFile(GL_FRAGMENT_SHADER, fragment_path);
    if (fragmentShader == 0) {
        std::cerr << "Failed to load fragment shader " << fragment_path << " ." << std::endl;
        return 0;
    }


    GLuint shaders[] = {vertexShader, fragmentShader, 0};
    GLuint program = createProgram(shaders);
    if (program == 0) {
        std::cerr << "Failed to create program." << std::endl;
        return 0;
    }

    return program;
}

unsigned int Shader::loadShader(const char *vertex_path, const char *fragment_path, const char *geometry_path) {
    GLuint vertexShader = createShaderFromFile(GL_VERTEX_SHADER, vertex_path);
    if (vertexShader == 0) {
        std::cerr << "Failed to load vertex shader " << vertex_path << " ." << std::endl;
        return 0;
    }
    GLuint fragmentShader = createShaderFromFile(GL_FRAGMENT_SHADER, fragment_path);
    if (fragmentShader == 0) {
        std::cerr << "Failed to load fragment shader " << fragment_path << " ." << std::endl;
        return 0;
    }
    GLuint geometryShader = createShaderFromFile(GL_GEOMETRY_SHADER, geometry_path);
    if (geometryShader == 0) {
        std::cerr << "Failed to load geometry shader " << geometry_path << " ." << std::endl;
        return 0;
    }


    GLuint shaders[] = {vertexShader, fragmentShader, geometryShader, 0};
    GLuint program = createProgram(shaders);
    if (program == 0) {
        std::cerr << "Failed to create program." << std::endl;
        return 0;
    }

    return program;
}

