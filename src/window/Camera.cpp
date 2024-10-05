//
// Created by korikmat on 04.03.2024.
//

#include "Camera.h"

Camera::Camera(glm::vec3 position, float fov) : fov(fov), position(position), rotation(1.0f) {
    updateVectors();
}

Camera::Camera(size_t ID, glm::vec3 position, float fov) : ID(ID), fov(fov), position(position), rotation(1.0f) {
    model = std::make_shared<Model>("res/camera/camera.obj", ID);
    model->position = position;
    model->scale = glm::vec3(0.3f);
    updateVectors();
}

void Camera::update() {
    model->position = position;
}

void Camera::draw(Shader &shader) {
    model->draw(shader);
}

void Camera::updateVectors() {
    glm::mat4 rotationMatrix = glm::toMat4(quatRotation);
    front = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f)));
    right = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f)));
    up = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f)));
}

void Camera::rotate(float x, float y, float z) {
    if (lock || !Events::cursorLocked) return;
    updateAngles(x, y, z);
    rotation = glm::mat4(1.0f);
    rotation = Zangle != 0 ? glm::rotate(rotation, Zangle, glm::vec3(0.0f, 0.0f, 1.0f)) : rotation;
    rotation = Yangle != 0 ? glm::rotate(rotation, Yangle, glm::vec3(0.0f, 1.0f, 0.0f)) : rotation;
    rotation = Xangle != 0 ? glm::rotate(rotation, Xangle, glm::vec3(1.0f, 0.0f, 0.0f)) : rotation;


    updateVectors();
}

void Camera::applyRotation(float x, float y, float z) {
    if (lock || !Events::cursorLocked) return;
    quatRotation = glm::angleAxis(x, right) * quatRotation;
    quatRotation = glm::angleAxis(y, glm::vec3(0.0f, 1.0f, 0.0f)) * quatRotation;
    quatRotation = glm::angleAxis(z, glm::vec3(0.0f, 0.0f, 1.0f)) * quatRotation;

    updateVectors();
}

glm::mat4 Camera::getProjection() {
    if (aspect == 0.0f) {
        aspect = (float) Window::WIDTH / (float) Window::HEIGHT;
    }
    if (perspective)
        return glm::perspective(glm::radians(fov), aspect, 0.1f, 500.0f);
    else if (flipped)
        return glm::ortho(0.0f, fov * aspect, fov, 0.0f);
    else
        return glm::ortho(0.0f, fov * aspect, 0.0f, fov);
}

glm::mat4 Camera::getView() {
    if (perspective)
        return glm::lookAt(position, position + front, up);
    else
        return glm::translate(glm::mat4(1.0f), position);
}

void Camera::updateAngles(float x, float y, float z) {
    this->Xangle = (this->Xangle - x > 2 * M_PI) || (this->Xangle - x < -2 * M_PI) ? 0 : this->Xangle - x;
    this->Yangle = (this->Yangle - y > 2 * M_PI) || (this->Yangle - y < -2 * M_PI) ? 0 : this->Yangle - y;
    this->Zangle = (this->Zangle - z > 2 * M_PI) || (this->Zangle - z < -2 * M_PI) ? 0 : this->Zangle - z;
}

void Camera::moveForward(float deltaTime) {
    if (lock || !Events::cursorLocked) return;
    position += glm::normalize(front * glm::vec3(1.0f, 0.0f, 1.0f)) * speed * deltaTime;
    if (!isInside()) position -= glm::normalize(front * glm::vec3(1.0f, 0.0f, 1.0f)) * speed * deltaTime;
}

void Camera::moveBackward(float deltaTime) {
    if (lock || !Events::cursorLocked) return;
    position -= glm::normalize(front * glm::vec3(1.0f, 0.0f, 1.0f)) * speed * deltaTime;
    if (!isInside()) position += glm::normalize(front * glm::vec3(1.0f, 0.0f, 1.0f)) * speed * deltaTime;
}

void Camera::moveLeft(float deltaTime) {
    if (lock || !Events::cursorLocked) return;
    position -= glm::normalize(right) * speed * deltaTime;
    if (!isInside()) position += glm::normalize(right) * speed * deltaTime;
}

void Camera::moveRight(float deltaTime) {
    if (lock || !Events::cursorLocked) return;
    position += glm::normalize(right) * speed * deltaTime;
    if (!isInside()) position -= glm::normalize(right) * speed * deltaTime;
}

void Camera::moveUp(float deltaTime) {
    if (lock || !Events::cursorLocked) return;
    position += glm::vec3(0.0f, 1.0f, 0.0f) * speed * deltaTime;
    if (!isInside()) position -= glm::vec3(0.0f, 1.0f, 0.0f) * speed * deltaTime;
}

void Camera::moveDown(float deltaTime) {
    if (lock || !Events::cursorLocked) return;
    position -= glm::vec3(0.0f, 1.0f, 0.0f) * speed * deltaTime;
    if (!isInside()) position += glm::vec3(0.0f, 1.0f, 0.0f) * speed * deltaTime;
}

bool Camera::isInside() {
    return position.x > -500.0 && position.x < 500.0 && position.y > -500.0 && position.y < 500.0 &&
           position.z > -500.0 && position.z < 500.0;
}
