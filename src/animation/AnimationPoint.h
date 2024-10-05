/// @file AnimationPoint.h
/// @brief This file contains the definition of the AnimationPoint class.
///
/// Created by korikmat on 20.05.2024.

#ifndef PROJECT_ANIMATIONPOINT_H
#define PROJECT_ANIMATIONPOINT_H

#include "../graphics/models/Model.h"

/// @brief Class representing an animation point in the graphics model.
class AnimationPoint;

using AnimationPointPtr = std::shared_ptr<AnimationPoint>;

/// @class AnimationPoint
/// @brief The AnimationPoint class is used to define points of animation within a model.
/// @details This class inherits from the Model class and adds functionality specific to animation points.
class AnimationPoint : public Model {
public:
    /// @brief A flag indicating whether the animation point is hidden.
    bool hide = false;

    /// @brief Constructor for AnimationPoint.
    /// @param path The file path to the animation point object. Default is "res/animation/animation_point.obj".
    /// @param ID The unique identifier for the animation point. Default is 0.
    /// @param copy A flag indicating whether the animation point is a copy. Default is false.
    AnimationPoint(std::string const &path = "res/animation/animation_point.obj", size_t ID = 0, bool copy = false);
};

#endif //PROJECT_ANIMATIONPOINT_H
