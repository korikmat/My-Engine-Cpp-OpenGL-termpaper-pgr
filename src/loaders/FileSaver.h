/// @file FileSaver.h
/// @brief This file contains the definition of the FileSaver class.
///
/// Created by korikmat on 20.05.2024.

#ifndef PROJECT_FILESAVER_H
#define PROJECT_FILESAVER_H

#include <string>
#include <iostream>
#include <fstream>

#include "glm/vec4.hpp"
#include "glm/vec3.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/compatibility.hpp>

#define READ 0
#define WRITE 1

/// @class FileSaver
/// @brief The FileSaver class provides functionality for saving and loading various data types to and from a binary file.
/// @details This class supports saving and loading matrices, vectors, quaternions, and other data types, facilitating easy file operations.
class FileSaver {
public:
    /// @brief Constructs a FileSaver object with the specified mode and file name.
    /// @param mode The mode of operation (READ or WRITE).
    /// @param sceneNameBin The name of the binary file. Default is "default.bin".
    explicit FileSaver(bool mode, std::string sceneNameBin = "default.bin");

    /// @brief Destructor for FileSaver.
    ~FileSaver();

    /// @brief Gets the status of the file stream.
    /// @return True if the file stream is in a good state, false otherwise.
    bool getStatus();

    /// @brief Saves a 4x4 matrix to the file.
    /// @param matrix The matrix to save.
    void saveToFile(glm::mat4 &matrix);

    /// @brief Saves a 4D vector to the file.
    /// @param vector The vector to save.
    void saveToFile(glm::vec4 &vector);

    /// @brief Saves a quaternion to the file.
    /// @param quaternion The quaternion to save.
    void saveToFile(glm::quat &quaternion);

    /// @brief Saves a 3D vector to the file.
    /// @param vector The vector to save.
    void saveToFile(glm::vec3 &vector);

    /// @brief Saves a float value to the file.
    /// @param value The value to save.
    void saveToFile(float value);

    /// @brief Saves a boolean value to the file.
    /// @param value The value to save.
    void saveToFile(bool value);

    /// @brief Saves a size_t value to the file.
    /// @param value The value to save.
    void saveToFile(size_t value);

    /// @brief Saves a string to the file.
    /// @param value The string to save.
    void saveToFile(std::string &value);

    /// @brief Saves a vector of size_t values to the file.
    /// @param vector The vector to save.
    void saveToFile(std::vector<size_t> &vector);

    /// @brief Loads a 4x4 matrix from the file.
    /// @param matrix The matrix to load.
    void loadFromFile(glm::mat4 &matrix);

    /// @brief Loads a 4D vector from the file.
    /// @param vector The vector to load.
    void loadFromFile(glm::vec4 &vector);

    /// @brief Loads a quaternion from the file.
    /// @param quaternion The quaternion to load.
    void loadFromFile(glm::quat &quaternion);

    /// @brief Loads a 3D vector from the file.
    /// @param vector The vector to load.
    void loadFromFile(glm::vec3 &vector);

    /// @brief Loads a float value from the file.
    /// @param value The value to load.
    void loadFromFile(float &value);

    /// @brief Loads a boolean value from the file.
    /// @param value The value to load.
    void loadFromFile(bool &value);

    /// @brief Loads a size_t value from the file.
    /// @param value The value to load.
    void loadFromFile(size_t &value);

    /// @brief Loads a string from the file.
    /// @param value The string to load.
    void loadFromFile(std::string &value);

    /// @brief Loads a vector of size_t values from the file.
    /// @param vector The vector to load.
    void loadFromFile(std::vector<size_t> &vector);

private:
    /// @brief The file stream used for reading and writing.
    std::fstream file;

    /// @brief Checks for errors in the file stream.
    void checkError();
};

#endif //PROJECT_FILESAVER_H
