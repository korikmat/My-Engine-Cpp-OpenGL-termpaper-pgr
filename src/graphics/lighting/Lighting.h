/// @file Lighting.h
/// @brief This file contains the definition of the Lighting class and related structures.
///
/// Created by korikmat on 12.05.2024.

#ifndef PROJECT_LIGHTING_H
#define PROJECT_LIGHTING_H

#include <vector>
#include "Light.h"
#include "glm/ext/matrix_float4x4.hpp"
#include "Fog.h"

/// @struct Sun
/// @brief Represents the sun in the scene with its direction, color, and enabled state.
struct Sun {
    /// @brief The direction of the sun.
    glm::vec3 direction;

    /// @brief The color of the sun.
    glm::vec3 color;

    /// @brief Flag indicating whether the sun is enabled.
    bool enabled;
};

/// @struct LightData
/// @brief Contains the data for a light source, used for uniform buffer objects.
/// @details The structure includes position, color, attenuation, direction/angle, and view-projection matrices.
struct LightData {
    alignas(16) glm::vec3 position; ///< The position of the light.
    alignas(16) glm::vec3 color; ///< The color of the light.
    alignas(16) glm::vec3 attenuation; ///< The attenuation factors of the light.
    alignas(16) glm::vec4 direction_angle; ///< The direction and angle of the light.
    alignas(16) glm::mat4 vp[6]; ///< The view-projection matrices for the light.
};

#define MAX_LIGHTS 10 ///< The maximum number of lights supported.

/// @class Lighting
/// @brief The Lighting class manages multiple light sources and their data.
/// @details This class handles the creation and management of lights, updating their data, and managing uniform buffer objects.
class Lighting {
public:
    /// @brief A vector of light pointers representing the light sources.
    std::vector<LightPtr> lights;

    /// @brief An array of light data for use with uniform buffer objects.
    LightData lightsData[MAX_LIGHTS];

    /// @brief The uniform buffer object (UBO) for the lights.
    unsigned int ubo;

    /// @brief The sun in the scene.
    Sun sun;

    /// @brief The fog settings for the scene.
    Fog fog = Fog();

    /// @brief Constructs a Lighting object and initializes the lighting system.
    Lighting();

    /// @brief Creates the uniform buffer object for the lights.
    void createUBO();

    /// @brief Adds a point light to the scene.
    /// @param ID The unique identifier for the light.
    /// @param position The position of the point light.
    /// @param color The color of the point light.
    void addPointLight(size_t ID, glm::vec3 position, glm::vec3 color);

    /// @brief Adds a spot light to the scene.
    /// @param ID The unique identifier for the light.
    /// @param position The position of the spot light.
    /// @param color The color of the spot light.
    /// @param direction_angle The direction and angle of the spot light.
    void addSpotLight(size_t ID, glm::vec3 position, glm::vec3 color, glm::vec4 direction_angle);

    /// @brief Updates the lighting data.
    void update();

    /// @brief Recalculates the view-projection matrices for a specific light.
    /// @param idx The index of the light to update.
    void recalcVP(int idx);

    /// @brief Draws the lights using the specified shader.
    /// @param shader The shader program used for rendering.
    void draw(Shader &shader);

    /// @brief Generates a random color value.
    /// @return A random float value representing a color component.
    float getRandomColor();

private:
    /// @brief Adds a light to the internal vector of lights.
    /// @param light The light pointer to be added.
    void add(const LightPtr &light);
};

#endif //PROJECT_LIGHTING_H
