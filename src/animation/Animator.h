/// @file Animator.h
/// @brief This file contains the definition of the Animator class.
///
/// Created by korikmat on 20.05.2024.

#ifndef PROJECT_ANIMATOR_H
#define PROJECT_ANIMATOR_H

#include "../graphics/models/Model.h"
#include "AnimationPoint.h"

#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/compatibility.hpp>

/// @class Animator
/// @brief The Animator class is responsible for animating objects using different interpolation methods.
class Animator {
public:
    /// @brief The speed of the animation.
    float speed = 10.0f;

    /// @brief Default constructor for Animator.
    Animator();

    /// @brief Performs linear interpolation on the position and rotation based on the given animation points and delta time.
    /// @param position The position to be updated.
    /// @param rotation The rotation to be updated.
    /// @param points The vector of animation points to interpolate between.
    /// @param deltaTime The time delta for the interpolation.
    void linear(glm::vec3 &position, glm::quat &rotation, std::vector<AnimationPointPtr> &points, float deltaTime);

    /// @brief Performs Catmull-Rom spline interpolation on the position and rotation based on the given animation points and delta time.
    /// @param position The position to be updated.
    /// @param rotation The rotation to be updated.
    /// @param points The vector of animation points to interpolate between.
    /// @param deltaTime The time delta for the interpolation.
    void catmullRom(glm::vec3 &position, glm::quat &rotation, std::vector<AnimationPointPtr> &points, float deltaTime);

private:
    /// @brief The current segment of the animation.
    int segment = 0;

    /// @brief The interpolation parameter.
    float t = 0.0f;

    /// @brief Performs linear interpolation between two points.
    /// @param start The start point.
    /// @param end The end point.
    /// @return The interpolated position.
    glm::vec3 linearInterpolation(glm::vec3 start, glm::vec3 end);

    /// @brief Performs Catmull-Rom spline interpolation between four points.
    /// @param p0 The first control point.
    /// @param p1 The second control point.
    /// @param p2 The third control point.
    /// @param p3 The fourth control point.
    /// @return The interpolated position.
    glm::vec3 catmullRomInterpolation(const glm::vec3 &p0, const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3);

    /// @brief Performs spherical linear interpolation (slerp) between two quaternions.
    /// @param start The start quaternion.
    /// @param end The end quaternion.
    /// @param t The interpolation parameter.
    /// @return The interpolated quaternion.
    glm::quat slerp(const glm::quat &start, const glm::quat &end, float t);
};

#endif //PROJECT_ANIMATOR_H

