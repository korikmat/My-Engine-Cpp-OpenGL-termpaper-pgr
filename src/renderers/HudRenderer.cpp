#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "HudRenderer.h"
#include "../graphics/Shader.h"
#include "../graphics/hud/Font.h"
#include "../graphics/hud/Batch2D.h"
#include "../window/Camera.h"
#include "../window/Window.h"


HudRenderer::HudRenderer() {
    batch = new Batch2D(1024);
    uicamera = new Camera(glm::vec3(), (float) Window::HEIGHT / 1.0f);
    uicamera->perspective = false;
    uicamera->flipped = true;
}

HudRenderer::~HudRenderer() {
    delete batch;
    delete uicamera;
}

void HudRenderer::drawDebug(int fps) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);


    uiShader.use();
    uiShader.uniformInt("u_texture", 0);
    glActiveTexture(GL_TEXTURE0);
    uiShader.uniformMatrix("u_projview", uicamera->getProjection() * uicamera->getView());
    batch->color = vec4(1.0f);
    batch->begin();

    font.draw(batch, L"fps:" + std::to_wstring(fps), 10, 10, STYLE_OUTLINE);

    batch->render();


    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
}



