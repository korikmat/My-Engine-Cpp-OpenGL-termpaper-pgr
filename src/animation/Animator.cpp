//
// Created by korikmat on 20.05.2024.
//

#include "Animator.h"

Animator::Animator() {

}


void
Animator::linear(glm::vec3 &position, glm::quat &rotation, std::vector<AnimationPointPtr> &points, float deltaTime) {

    glm::vec3 start = points[segment]->position;
    glm::vec3 end = points[(segment + 1) % points.size()]->position;
    float distance = glm::length(end - start);

    t += (speed * deltaTime) / distance;

    if (t >= 1.0f) {
        t = 0.0f;
        segment = (segment + 1) % points.size();
    }

    position = linearInterpolation(points[segment]->position,
                                   points[(segment + 1) % points.size()]->position);
    rotation = slerp(points[segment]->quatRotation, points[(segment + 1) % points.size()]->quatRotation, t);
}

void Animator::catmullRom(glm::vec3 &position, glm::quat &rotation, std::vector<AnimationPointPtr> &points,
                          float deltaTime) {

    float distance = 0;

    glm::vec3 start;
    glm::vec3 end;
    for (size_t i = 0; i < 4; i++) {
        start = points[(segment + i) % points.size()]->position;
        end = points[(segment + i + 1) % points.size()]->position;
        distance += glm::length(end - start);

    }

    t += (speed * deltaTime) / distance;
    if (t >= 1.0f) {
        t = 0.0f;
        segment = (segment + 1) % points.size();
    }
    position = catmullRomInterpolation(
            points[(segment - 1 + points.size()) % points.size()]->position,
            points[(segment) % points.size()]->position,
            points[(segment + 1) % points.size()]->position,
            points[(segment + 2) % points.size()]->position);

    rotation = slerp(points[(segment) % points.size()]->quatRotation,
                     points[(segment + 1) % points.size()]->quatRotation, t);
}

glm::vec3 Animator::linearInterpolation(glm::vec3 start, glm::vec3 end) {
    return start + t * (end - start);
}

glm::vec3
Animator::catmullRomInterpolation(const glm::vec3 &p0, const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3) {
    float t2 = t * t;
    float t3 = t2 * t;

    return 0.5f * (p0 * (-t3 + 2.0f * t2 - t)
                   + p1 * (3.0f * t3 - 5.0f * t2 + 2.0f)
                   + p2 * (-3.0f * t3 + 4.0f * t2 + t)
                   + p3 * (t3 - t2));
}

glm::quat Animator::slerp(const glm::quat &start, const glm::quat &end, float t) {
    return glm::slerp(start, end, t);
}