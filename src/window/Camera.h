/// @file Camera.h
/// @brief This file contains the definition of the Camera class.
///
/// Created by korma on 04.03.2024.

#ifndef PROJECT_CAMERA_H
#define PROJECT_CAMERA_H

#include <memory>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

#include "Window.h"
#include "Events.h"
#include "../graphics/models/Model.h"

class Camera;

using CameraPtr = std::shared_ptr<Camera>;

/// @class Camera
/// @brief The Camera class represents a camera in the scene.
/// @details This class handles camera movement, rotation, and view/projection matrix calculations.
class Camera {
public:
    /// @brief The unique identifier for the camera.
    size_t ID = 0;

    /// @brief The front vector of the camera.
    glm::vec3 front;

    /// @brief The up vector of the camera.
    glm::vec3 up;

    /// @brief The right vector of the camera.
    glm::vec3 right;

    /// @brief The field of view of the camera.
    float fov;

    /// @brief The position of the camera.
    glm::vec3 position;

    /// @brief The rotation matrix of the camera.
    glm::mat4 rotation;

    /// @brief The quaternion representing the camera's rotation.
    glm::quat quatRotation = glm::quat(0.0f, 0.0f, 1.0f, 0.0f);

    /// @brief Flag indicating whether the camera uses perspective projection.
    bool perspective = true;

    /// @brief Flag indicating whether the camera is flipped.
    bool flipped = false;

    /// @brief The aspect ratio of the camera.
    float aspect = 0.0f;

    /// @brief Flag indicating whether the camera is locked.
    bool lock = false;

    /// @brief The movement speed of the camera.
    float speed = 7.0f;

    /// @brief Flag indicating whether the camera is active.
    bool active = false;

    /// @brief The distance from the camera to the target.
    float cameraDistance = 0;

    /// @brief Flag indicating whether the camera is in selection mode.
    bool selectionMode = false;

    /// @brief Flag indicating whether the camera is animated.
    bool animated = false;

    /// @brief The type of animation interpolation (true for linear, false for Catmull-Rom).
    bool animationType = CATMULLROM_INTERPOLATION;

    /// @brief Constructs a Camera object with the specified position and field of view.
    /// @param position The initial position of the camera.
    /// @param fov The field of view of the camera.
    Camera(glm::vec3 position, float fov);

    /// @brief Constructs a Camera object with the specified ID, position, and field of view.
    /// @param ID The unique identifier for the camera.
    /// @param position The initial position of the camera.
    /// @param fov The field of view of the camera.
    Camera(size_t ID, glm::vec3 position, float fov);

    /// @brief Updates the camera state.
    void update();

    /// @brief Draws the camera using the specified shader.
    /// @param shader The shader program used for rendering.
    void draw(Shader &shader);

    /// @brief Updates the camera's front, up, and right vectors based on its rotation.
    void updateVectors();

    /// @brief Rotates the camera by the specified angles.
    /// @param x The angle to rotate around the x-axis.
    /// @param y The angle to rotate around the y-axis.
    /// @param z The angle to rotate around the z-axis.
    void rotate(float x, float y, float z);

    /// @brief Applies a rotation to the camera by the specified angles.
    /// @param x The angle to rotate around the x-axis.
    /// @param y The angle to rotate around the y-axis.
    /// @param z The angle to rotate around the z-axis.
    void applyRotation(float x, float y, float z);

    /// @brief Gets the projection matrix of the camera.
    /// @return The projection matrix.
    glm::mat4 getProjection();

    /// @brief Gets the view matrix of the camera.
    /// @return The view matrix.
    glm::mat4 getView();

    /// @brief Updates the camera's rotation angles.
    /// @param x The new x-axis rotation angle.
    /// @param y The new y-axis rotation angle.
    /// @param z The new z-axis rotation angle.
    void updateAngles(float x, float y, float z);

    /// @brief Moves the camera forward.
    /// @param deltaTime The time elapsed since the last update.
    void moveForward(float deltaTime);

    /// @brief Moves the camera backward.
    /// @param deltaTime The time elapsed since the last update.
    void moveBackward(float deltaTime);

    /// @brief Moves the camera to the left.
    /// @param deltaTime The time elapsed since the last update.
    void moveLeft(float deltaTime);

    /// @brief Moves the camera to the right.
    /// @param deltaTime The time elapsed since the last update.
    void moveRight(float deltaTime);

    /// @brief Moves the camera up.
    /// @param deltaTime The time elapsed since the last update.
    void moveUp(float deltaTime);

    /// @brief Moves the camera down.
    /// @param deltaTime The time elapsed since the last update.
    void moveDown(float deltaTime);

    /// @brief Checks if the camera is inside a model.
    /// @return True if the camera is inside a model, false otherwise.
    bool isInside();

    /// @brief The model associated with the camera.
    ModelPtr model = nullptr;

    /// @brief The x-axis rotation angle.
    float Xangle = 0.0f;

    /// @brief The y-axis rotation angle.
    float Yangle = 0.0f;

    /// @brief The z-axis rotation angle.
    float Zangle = 0.0f;
};

#endif //PROJECT_CAMERA_H
