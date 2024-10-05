//
// Created by korikmat on 12.05.2024.
//

#include "Light.h"
#include "glm/geometric.hpp"

Light::Light(size_t ID, glm::vec3 position, glm::vec3 color, glm::vec4 direction_angle ) : Model("res/lights/light.obj", ID), color(color), direction_angle(direction_angle) {
    this->position = position;
    this->direction_angle = glm::vec4( glm::normalize(glm::vec3(direction_angle)), direction_angle.w);
    this->scale = glm::vec3(0.1f);
}