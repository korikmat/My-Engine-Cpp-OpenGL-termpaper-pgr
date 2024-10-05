//
// Created by korikmat on 20.05.2024.
//

#include <iostream>
#include "AnimationPoint.h"

AnimationPoint::AnimationPoint(std::string const &path, size_t ID, bool copy) : Model(path, ID, copy) {
    this->scale = glm::vec3(0.12f);
}