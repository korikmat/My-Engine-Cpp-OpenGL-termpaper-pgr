/// @file Renderer.h
/// @brief This file contains the definition of the Renderer class.
///
/// Created by korikmat on 20.05.2024.

#ifndef PROJECT_RENDERER_H
#define PROJECT_RENDERER_H

#include <unordered_map>
#include "../graphics/models/Model.h"
#include "../window/Camera.h"
#include "../graphics/TextureCubeArray.h"
#include "../graphics/lighting/Lighting.h"
#include "../graphics/gBuffer.h"
#include "../graphics/SkyBox.h"
#include "../graphics/AxesCrosshair.h"

/// @class Renderer
/// @brief The Renderer class is responsible for rendering the scene.
/// @details This class handles shadow mapping, geometry rendering, lighting, skybox, and crosshair rendering.
class Renderer {
public:
    /// @brief Shader for shadow mapping.
    Shader shadowShader = Shader("res/shadowDepth.vert", "res/shadowDepth.frag", "res/shadowDepth.geom");

    /// @brief Shader for the geometry pass.
    Shader shaderGeometryPass = Shader("res/shaderGeometry.vert", "res/shaderGeometry.frag");

    /// @brief Shader for the geometry pass with mountains.
    Shader shaderGeometryPassMountains = Shader("res/shaderGeometryMountains.vert", "res/shaderGeometryMountains.frag");

    /// @brief Shader for the animated TV screen.
    Shader animatedTvScreen = Shader("res/animatedTvScreen.vert", "res/animatedTvScreen.frag");

    /// @brief Shader for outlining.
    Shader outlineShader = Shader("res/outlining.vert", "res/outlining.frag");

    /// @brief Shader for the lighting pass.
    Shader shaderLightingPassNew = Shader("res/shaderLighting.vert", "res/shaderLighting.frag");

    /// @brief Shader for the skybox.
    Shader skyboxShader = Shader("res/skybox.vert", "res/skybox.frag");

    /// @brief Shader for the axes crosshair.
    Shader AxesCrosshairShader = Shader("res/axesCrosshair.vert", "res/axesCrosshair.frag");

    /// @brief Texture cube array for shadow mapping.
    TextureCubeArray textureCubeArray = TextureCubeArray(MAX_LIGHTS);

    /// @brief G-buffer for deferred rendering.
    gBuffer gbuffer = gBuffer();

    /// @brief Vertex Array Object for rendering a quad.
    unsigned int quadVAO = 0;

    /// @brief Vertex Buffer Object for rendering a quad.
    unsigned int quadVBO;

    /// @brief Constructs a Renderer object.
    Renderer();

    /// @brief Renders shadows for the given models and camera.
    /// @param models The models to render shadows for.
    /// @param camera The camera used for rendering shadows.
    /// @param lightsCount The number of lights to consider for shadow rendering.
    void renderShadows(std::unordered_map<size_t, ModelPtr> &models, CameraPtr &camera, size_t lightsCount);

    /// @brief Renders the geometry pass for the given models and cameras.
    /// @param models The models to render.
    /// @param cameras The cameras used for rendering.
    /// @param lightingSystem The lighting system for the scene.
    void renderGeometry(std::unordered_map<size_t, ModelPtr> &models, std::vector<CameraPtr> &cameras, Lighting &lightingSystem);

    /// @brief Renders the lighting pass.
    /// @param camera The camera used for rendering.
    /// @param lightingSystem The lighting system for the scene.
    void renderLighting(CameraPtr &camera, Lighting &lightingSystem);

    /// @brief Renders the skybox.
    /// @param skybox The skybox to render.
    /// @param camera The camera used for rendering.
    /// @param lightingSystem The lighting system for the scene.
    void renderSkybox(SkyBox &skybox, CameraPtr &camera, Lighting &lightingSystem);

    /// @brief Renders the axes crosshair.
    /// @param crosshair The axes crosshair to render.
    /// @param camera The camera used for rendering.
    void renderCrosshair(AxesCrosshair &crosshair, CameraPtr &camera);

private:
    /// @brief Renders a quad.
    void renderQuad();
};

#endif //PROJECT_RENDERER_H
