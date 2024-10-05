//
// Created by korikmat on 30.03.2024.
//

#include <iostream>
#include "Model.h"
#include "../../loaders/ModelLoader.h"
#include "../../class_factory/ClassFactory.h"
#include "glm/gtx/transform.hpp"

Model::Model(std::string const &path, size_t ID, bool copy) : ID(ID), path(path),
                                                              isCopy(copy) {
    if (!isCopy) {
        ModelLoader modelLoader;
        this->meshes = modelLoader.loadModel(path);
        std::cout << "New model " << path << " was loaded from files!" << std::endl;
    }
}

Model::~Model() {
    std::cout << "Model data " << path << " was erased!" << std::endl;
}

void Model::draw(Shader &shader) {
    shader.uniformMatrix("model", getModelMatrixQuat());
    for (auto &mesh: meshes) {
        mesh->draw(shader);
    }
}

void Model::update() {}

ModelPtr Model::copy(size_t ID) {
    ModelPtr copy = ClassFactory::instance().create(className, this->path, ID, true);
    copy->position = this->position;
    copy->quatRotation = this->quatRotation;
    copy->cameraDistance = this->cameraDistance;
    copy->view = this->view;
    copy->projection = this->projection;
    copy->meshes = this->meshes;
    copy->className = this->className;
    copy->scale = this->scale;
    return copy;
}

void Model::applyRotation(float angle, glm::vec3 axis) {
//    quatRotation = glm::angleAxis(glm::radians(angle), axis) * quatRotation;
    quatRotation = glm::angleAxis(angle, axis) * quatRotation;

}

glm::mat4 Model::getModelMatrixQuat() {
    glm::mat4 translateMat = glm::translate(position);
    glm::mat4 rotateMat = glm::toMat4(quatRotation);
    glm::mat4 scaleMat = glm::scale(scale);
    return translateMat * rotateMat * scaleMat;
}

