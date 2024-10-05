/// @file Shader.h
/// @brief This file contains the definition of the Shader class and related functions.
///
/// Created by korikmat on 27.02.2024.

#ifndef PROJECT_SHADER_H
#define PROJECT_SHADER_H

#include <glm/mat4x4.hpp>

/// @class Shader
/// @brief The Shader class handles the compilation and management of shader programs.
/// @details This class provides methods for loading, compiling, and using shaders, as well as setting uniform variables in the shader programs.
class Shader {
public:
    /// @brief The ID of the shader program.
    unsigned int id;

    /// @brief Constructs a Shader object with the specified vertex and fragment shader paths.
    /// @param vertex_path The file path to the vertex shader.
    /// @param fragment_path The file path to the fragment shader.
    explicit Shader(const char *vertex_path, const char *fragment_path);

    /// @brief Constructs a Shader object with the specified vertex, fragment, and geometry shader paths.
    /// @param vertex_path The file path to the vertex shader.
    /// @param fragment_path The file path to the fragment shader.
    /// @param geometry_path The file path to the geometry shader.
    explicit Shader(const char *vertex_path, const char *fragment_path, const char *geometry_path);

    /// @brief Destructor for Shader.
    ~Shader();

    /// @brief Uses the shader program.
    void use();

    /// @brief Sets a mat4 uniform variable in the shader.
    /// @param name The name of the uniform variable.
    /// @param matrix The mat4 value to set.
    void uniformMatrix(const char *name, glm::mat4 matrix);

    /// @brief Sets a mat3 uniform variable in the shader.
    /// @param name The name of the uniform variable.
    /// @param matrix The mat3 value to set.
    void uniformMat3(const char *name, glm::mat3 matrix);

    /// @brief Sets a bool uniform variable in the shader.
    /// @param name The name of the uniform variable.
    /// @param value The bool value to set.
    void uniformBool(const char *name, bool value);

    /// @brief Sets an int uniform variable in the shader.
    /// @param name The name of the uniform variable.
    /// @param value The int value to set.
    void uniformInt(const char *name, int value);

    /// @brief Sets a vec2 uniform variable in the shader.
    /// @param name The name of the uniform variable.
    /// @param vec The vec2 value to set.
    void uniformVec2(const char *name, glm::vec2 vec);

    /// @brief Sets a vec3 uniform variable in the shader.
    /// @param name The name of the uniform variable.
    /// @param vec The vec3 value to set.
    void uniformVec3(const char *name, glm::vec3 vec);

    /// @brief Sets a vec4 uniform variable in the shader.
    /// @param name The name of the uniform variable.
    /// @param vec The vec4 value to set.
    void uniformVec4(const char *name, glm::vec4 vec);

    /// @brief Sets a float uniform variable in the shader.
    /// @param name The name of the uniform variable.
    /// @param value The float value to set.
    void uniformFloat(const char *name, float value);

    /// @brief Loads and compiles a shader program with vertex and fragment shaders.
    /// @param vertex_path The file path to the vertex shader.
    /// @param fragment_path The file path to the fragment shader.
    /// @return The ID of the compiled shader program.
    unsigned int loadShader(const char *vertex_path, const char *fragment_path);

    /// @brief Loads and compiles a shader program with vertex, fragment, and geometry shaders.
    /// @param vertex_path The file path to the vertex shader.
    /// @param fragment_path The file path to the fragment shader.
    /// @param geometry_path The file path to the geometry shader.
    /// @return The ID of the compiled shader program.
    unsigned int loadShader(const char *vertex_path, const char *fragment_path, const char *geometry_path);
};

/// @brief Checks for OpenGL errors and reports them.
/// @param where A description of where the error check is taking place.
/// @param line The line number where the error check is taking place.
void checkGLError(const char *where, int line);

#endif //PROJECT_SHADER_H
