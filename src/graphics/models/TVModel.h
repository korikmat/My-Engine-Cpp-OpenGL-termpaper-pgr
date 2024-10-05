/// @file TVModel.h
/// @brief This file contains the definition of the TVModel class.
///
/// Created by korikmat on 19.05.2024.

#ifndef PROJECT_TVMODEL_H
#define PROJECT_TVMODEL_H

#include "Model.h"
#include "TVScreen.h"

/// @class TVModel
/// @brief The TVModel class represents a 3D model of a TV with an integrated screen.
/// @details This class inherits from the Model class and includes additional functionality specific to a TV model, such as a screen.
class TVModel : public Model {
public:
    /// @brief The TV screen associated with the TV model.
    TVScreen tvScreen;

    /// @brief Constructs a TVModel object with the specified path and ID.
    /// @param path The file path to the TV model. Default is "res/tv/tv.obj".
    /// @param ID The unique identifier for the TV model. Default is 0.
    /// @param copy Flag indicating whether the model is a copy. Default is true.
    TVModel(std::string const &path = "res/tv/tv.obj", size_t ID = 0, bool copy = true);

    /// @brief Draws the TV model using the specified shader.
    /// @param shader The shader program used for rendering.
    void draw(Shader &shader) override;

    /// @brief Updates the TV model's state.
    void update() override;

    /// @brief Checks if a point is inside the TV model.
    /// @param point The point to check.
    /// @return True if the point is inside the TV model, false otherwise.
    bool isInside(glm::vec3 point);

private:
    /// @brief The Vertex Array Object (VAO) for the TV model.
    unsigned int vao_;

    /// @brief The Vertex Buffer Object (VBO) for the TV model.
    unsigned int vbo_;

    /// @brief The Element Buffer Object (EBO) for the TV model.
    unsigned int ebo_;

    /// @brief The texture associated with the TV model.
    TexturePtr texture_;

    /// @brief Creates the buffers for the TV model.
    void createBuffers();
};

#endif //PROJECT_TVMODEL_H
