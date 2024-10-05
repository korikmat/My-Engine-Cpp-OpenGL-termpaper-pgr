/// @file Model.h
/// @brief This file contains the definition of the Model class.
///
/// Created by korikmat on 30.03.2024.

#ifndef PROJECT_MODEL_H
#define PROJECT_MODEL_H

#include <string>
#include <memory>
#include "assimp-5.3.1/include/assimp/Importer.hpp"
#include "assimp-5.3.1/include/assimp/scene.h"
#include "assimp-5.3.1/include/assimp/postprocess.h"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/compatibility.hpp"

#include "../Texture.h"
#include "../Shader.h"
#include "Mesh.h"

#define LINEAR_INTERPOLATION true
#define CATMULLROM_INTERPOLATION false

class Model;

using ModelPtr = std::shared_ptr<Model>;

/// @class Model
/// @brief The Model class represents a 3D model in the scene.
/// @details This class handles loading, rendering, and managing 3D models, including their transformations and animations.
class Model {
public:
    /// @brief The unique identifier for the model.
    size_t ID;

    /// @brief The file path to the model.
    std::string path;

    /// @brief The class name of the model.
    std::string className = "Model";

    /// @brief A pointer to the parent model.
    ModelPtr parent = nullptr;

    /// @brief A vector of meshes that make up the model.
    std::vector<MeshPtr> meshes;

    /// @brief Flag indicating whether the model is a copy.
    bool isCopy = false;

    /// @brief Flag indicating whether the model should cast shadows.
    bool calculateShadow = false;

    /// @brief Flag indicating whether the model is animated.
    bool animated = false;

    /// @brief The type of animation interpolation (true for linear, false for Catmull-Rom).
    bool animationType = CATMULLROM_INTERPOLATION;

    /// @brief The position of the model in the scene.
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);

    /// @brief The quaternion representing the model's rotation.
    glm::quat quatRotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

    /// @brief The scale of the model.
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

    /// @brief The distance from the camera to the model.
    float cameraDistance = 0;

    /// @brief The view matrix for the model.
    glm::mat4 view = glm::mat4(1.0f);

    /// @brief The projection matrix for the model.
    glm::mat4 projection = glm::mat4(1.0f);

    /// @brief Flag indicating whether the model is in selection mode.
    bool selectionMode = false;

    /// @brief Flag indicating whether the model is in rotation mode.
    bool rotationMode = false;

    /// @brief Flag indicating whether the model is being interacted with.
    bool isInteracted = false;

    /// @brief Constructs a Model object with the specified path and ID.
    /// @param path The file path to the model.
    /// @param ID The unique identifier for the model.
    /// @param copy Flag indicating whether the model is a copy. Default is false.
    explicit Model(std::string const &path, size_t ID = 0, bool copy = false);

    /// @brief Destructor for Model.
    virtual ~Model();

    /// @brief Draws the model using the specified shader.
    /// @param shader The shader program used for rendering.
    virtual void draw(Shader &shader);

    /// @brief Updates the model's state.
    virtual void update();

    /// @brief Creates a copy of the model with a new ID.
    /// @param ID The unique identifier for the new model.
    /// @return A shared pointer to the new model.
    virtual ModelPtr copy(size_t ID);

    /// @brief Applies a rotation to the model.
    /// @param angle The angle of rotation.
    /// @param axis The axis of rotation.
    void applyRotation(float angle, glm::vec3 axis);

    /// @brief Gets the model matrix with the quaternion rotation applied.
    /// @return The model matrix.
    glm::mat4 getModelMatrixQuat();
};

#endif //PROJECT_MODEL_H
