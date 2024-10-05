//
// Created by korikmat on 20.05.2024.
//

#include <iostream>
#include <vector>
#include "FileSaver.h"

FileSaver::FileSaver(bool mode, std::string sceneNameBin) {
    if (mode == WRITE)
        file = std::fstream(sceneNameBin.c_str(), std::ios::out | std::ios::binary);
    else if (mode == READ)
        file = std::fstream(sceneNameBin.c_str(), std::ios::in | std::ios::binary);
}

FileSaver::~FileSaver() {
    file.close();
}

void FileSaver::checkError() {
    if (file.fail()) {
        std::cerr << "Failed to write/load to/from file\n";
        throw std::runtime_error("Failed to write/load to/from file");
    }
}

bool FileSaver::getStatus() {
    return file.is_open();
}

void FileSaver::saveToFile(glm::mat4 &matrix) {
    file.write(reinterpret_cast<char *>(&matrix), sizeof(glm::mat4));
    checkError();
}

void FileSaver::saveToFile(glm::vec4 &vector) {
    file.write(reinterpret_cast<char *>(&vector), sizeof(glm::vec4));
    checkError();
}

void FileSaver::saveToFile(glm::quat &quaternion) {
    file.write(reinterpret_cast<char *>(&quaternion), sizeof(glm::quat));
    checkError();
}

void FileSaver::saveToFile(glm::vec3 &vector) {
    file.write(reinterpret_cast<char *>(&vector), sizeof(glm::vec3));
    checkError();
}

void FileSaver::saveToFile(float value) {
    file.write(reinterpret_cast<char *>(&value), sizeof(float));
    checkError();
}

void FileSaver::saveToFile(bool value) {
    file.write(reinterpret_cast<char *>(&value), sizeof(bool));
    checkError();
}

void FileSaver::saveToFile(size_t value) {
    file.write(reinterpret_cast<char *>(&value), sizeof(size_t));
    checkError();
}

void FileSaver::saveToFile(std::string &value) {
    size_t size = value.size();
    file.write(reinterpret_cast<char *>(&size), sizeof(size_t));
    checkError();
    file.write(value.c_str(), size);
    checkError();
}

void FileSaver::saveToFile(std::vector<size_t> &vector) {
    size_t size = vector.size();
    file.write(reinterpret_cast<char *>(&size), sizeof(size_t));
    checkError();
    file.write(reinterpret_cast<char *>(vector.data()), size * sizeof(size_t));
    checkError();
}


void FileSaver::loadFromFile(glm::mat4 &matrix) {
    file.read(reinterpret_cast<char *>(&matrix), sizeof(glm::mat4));
    checkError();
}

void FileSaver::loadFromFile(glm::vec4 &vector) {
    file.read(reinterpret_cast<char *>(&vector), sizeof(glm::vec4));
    checkError();
}

void FileSaver::loadFromFile(glm::quat &quaternion) {
    file.read(reinterpret_cast<char *>(&quaternion), sizeof(glm::quat));
    checkError();
}

void FileSaver::loadFromFile(glm::vec3 &vector) {
    file.read(reinterpret_cast<char *>(&vector), sizeof(glm::vec3));
    checkError();
}

void FileSaver::loadFromFile(float &value) {
    file.read(reinterpret_cast<char *>(&value), sizeof(float));
    checkError();
}

void FileSaver::loadFromFile(bool &value) {
    file.read(reinterpret_cast<char *>(&value), sizeof(bool));
    checkError();
}

void FileSaver::loadFromFile(size_t &value) {
    file.read(reinterpret_cast<char *>(&value), sizeof(size_t));
    checkError();
}

void FileSaver::loadFromFile(std::string &value) {
    size_t size;
    file.read(reinterpret_cast<char *>(&size), sizeof(size_t));
    checkError();
    char *buffer = new char[size];
    file.read(buffer, size);
    checkError();
    value = std::string(buffer, size);
    delete[] buffer;
}

void FileSaver::loadFromFile(std::vector<size_t> &vector) {
    size_t size;
    file.read(reinterpret_cast<char *>(&size), sizeof(size_t));
    checkError();
    vector.resize(size);
    file.read(reinterpret_cast<char *>(vector.data()), size * sizeof(size_t));
    checkError();
}

