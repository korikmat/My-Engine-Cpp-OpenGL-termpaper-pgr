/// @file HudRenderer.h
/// @brief This file contains the definition of the HudRenderer class.
///
/// Created by korikmat.

#ifndef PROJECT_HUDRENDER_H_
#define PROJECT_HUDRENDER_H_

#include "../graphics/hud/Font.h"
#include "../graphics/Shader.h"

class Batch2D;
class Camera;
class Mesh;

/// @class HudRenderer
/// @brief The HudRenderer class is responsible for rendering the HUD (Heads-Up Display).
/// @details This class handles the rendering of HUD elements such as text and UI components using a 2D batch and a UI camera.
class HudRenderer {
    /// @brief The 2D batch renderer used for drawing HUD elements.
    Batch2D* batch;

    /// @brief The camera used for rendering the UI.
    Camera* uicamera;

    /// @brief The font used for rendering text.
    Font font = Font("res/font/font");

    /// @brief The shader used for rendering UI elements.
    Shader uiShader = Shader("res/ui/ui.vert", "res/ui/ui.frag");

public:
    /// @brief Constructs a HudRenderer object.
    HudRenderer();

    /// @brief Destructor for HudRenderer.
    ~HudRenderer();

    /// @brief Draws debug information such as the current FPS.
    /// @param fps The current frames per second to be displayed.
    void drawDebug(int fps);
};

#endif /* PROJECT_HUDRENDER_H_ */
