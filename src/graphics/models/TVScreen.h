/// @file TVScreen.h
/// @brief This file contains the definition of the TVScreen class.
///
/// Created by korikmat on 15.05.2024.

#ifndef PROJECT_TVSCREEN_H
#define PROJECT_TVSCREEN_H

#include "Model.h"

/// @class TVScreen
/// @brief The TVScreen class represents a TV screen within a TV model.
/// @details This class inherits from the Model class and adds functionality specific to a TV screen, such as handling channels.
class TVScreen : public Model {
public:
    /// @brief The ID of the current channel being displayed on the TV screen.
    int channelID = 0;

    /// @brief Constructs a TVScreen object with the specified path and ID.
    /// @param path The file path to the TV screen model.
    /// @param ID The unique identifier for the TV screen model. Default is 0.
    /// @param copy Flag indicating whether the model is a copy. Default is false.
    explicit TVScreen(std::string const &path, size_t ID = 0, bool copy = false);

    /// @brief Draws the TV screen using the specified shader.
    /// @param shader The shader program used for rendering.
    void draw(Shader &shader) override;

    /// @brief The shader used for rendering the TV screen.
    Shader shader = Shader("res/animatedTvScreen.vert", "res/animatedTvScreen.frag");
};

#endif //PROJECT_TVSCREEN_H
