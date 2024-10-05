/// @file Scene.h
/// @brief This file contains the definition of the Scene class.
///
/// Created by korikmat on 06.05.2024.

#ifndef PROJECT_SCENE_H
#define PROJECT_SCENE_H

#include <unordered_map>
#include <vector>
#include <string>

#include "../graphics/models/Model.h"
#include "../graphics/SkyBox.h"
#include "../window/Camera.h"
#include "../graphics/AxesCrosshair.h"
#include "../graphics/lighting/Lighting.h"
#include "../renderers/HudRenderer.h"
#include "../renderers/Renderer.h"
#include "../animation/AnimationPoint.h"
#include "../animation/Animator.h"
#include "../graphics/models/TVModel.h"

/// @class Scene
/// @brief The Scene class manages all elements within a scene, including models, cameras, animations, lighting, and rendering.
/// @details This class handles loading and saving the scene, updating elements, and rendering the scene.
class Scene {
public:
    /// @brief The name of the binary file used for saving and loading the scene.
    std::string sceneNameBin = "default.bin";

    /// @brief A vector of free IDs for assigning to new models.
    std::vector<size_t> freeIDs = {1};

    /// @brief A map of model IDs to model pointers.
    std::unordered_map<size_t, ModelPtr> models;

    /// @brief A vector of shared pointers to TV models.
    std::vector<std::shared_ptr<TVModel>> TVs;

    /// @brief A vector of camera pointers.
    std::vector<CameraPtr> cameras;

    /// @brief The index of the current camera.
    size_t currCamera = 0;

    /// @brief The animator for handling animations.
    Animator animator = Animator();

    /// @brief A vector of animation point pointers.
    std::vector<AnimationPointPtr> animationPoints;

    /// @brief The lighting system for the scene.
    Lighting lightingSystem = Lighting();

    /// @brief The main renderer for the scene.
    Renderer renderer = Renderer();

    /// @brief The HUD renderer for the scene.
    HudRenderer hudRenderer = HudRenderer();

    /// @brief The axes crosshair for the scene.
    AxesCrosshair axesCrosshair = AxesCrosshair();

    /// @brief The skybox for the scene.
    SkyBox skybox = SkyBox();

    /// @brief Constructs a Scene object with the specified scene name.
    /// @param sceneName The name of the scene. Default is "default.bin".
    Scene(std::string sceneName = "default.bin");

    /// @brief Saves the scene to a binary file.
    void saveScene();

    /// @brief Loads the scene from a binary file.
    void loadScene();

    /// @brief Updates the scene based on the elapsed time.
    /// @param deltaTime The time elapsed since the last update.
    void update(float deltaTime);

    /// @brief Draws the scene, including HUD elements.
    /// @param fps The current frames per second to display in the HUD.
    void draw(int fps);
};

#endif //PROJECT_SCENE_H
