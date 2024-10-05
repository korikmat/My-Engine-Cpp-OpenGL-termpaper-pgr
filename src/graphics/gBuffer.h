/// @file gBuffer.h
/// @brief This file contains the definition of the gBuffer class.
///
/// Created by korikmat on 11.05.2024.

#ifndef PROJECT_GBUFFER_H
#define PROJECT_GBUFFER_H

#include "GL/glew.h"

/// @class gBuffer
/// @brief The gBuffer class is used to handle the creation and management of a G-buffer for deferred shading.
/// @details This class initializes and manages the G-buffer, which contains multiple render targets for storing various components needed in deferred shading.
class gBuffer {
public:
    /// @brief The ID of the G-buffer.
    unsigned int gbuffer;

    /// @brief The ID of the texture storing positions.
    unsigned int gPosition;

    /// @brief The ID of the texture storing normals.
    unsigned int gNormal;

    /// @brief The ID of the texture storing diffuse color and shininess.
    unsigned int gDiffuseShininess;

    /// @brief The ID of the texture storing ambient and specular color.
    unsigned int gAmbientSpecular;

    /// @brief The ID of the render buffer object for depth.
    unsigned int rboDepth;

    /// @brief Array of color attachments.
    unsigned int attachments[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };

    /// @brief Constructs a gBuffer object and initializes the G-buffer.
    gBuffer();
};

#endif //PROJECT_GBUFFER_H
