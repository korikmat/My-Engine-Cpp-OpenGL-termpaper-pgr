//
// Created by korikmat on 20.05.2024.
//
#include "GL/glew.h"

#include "Renderer.h"
#include "../window/Window.h"
#include "../graphics/models/Terrain.h"
#include "glm/ext/matrix_transform.hpp"
#include "../animation/AnimationPoint.h"


Renderer::Renderer() {}

void Renderer::renderShadows(std::unordered_map<size_t, ModelPtr> &models, CameraPtr &camera, size_t lightsCount) {
    glViewport(0, 0, (int) textureCubeArray.SHADOW_WIDTH, (int) textureCubeArray.SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, textureCubeArray.depthMapFBO);

    textureCubeArray.bind();
    shadowShader.use();
    glClear(GL_DEPTH_BUFFER_BIT);
    for (int i = 0; i < (int)lightsCount; i++) {
        shadowShader.uniformInt("light_i", i);
        for (auto &pair: models) {
            auto model = pair.second;
            if (!model->calculateShadow) {
                continue;
            }
            model->draw(shadowShader);
        }
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::renderGeometry(std::unordered_map<size_t, ModelPtr> &models, std::vector<CameraPtr> &cameras,
                              Lighting &lightingSystem) {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // geometry pass: render scene's geometry/color data into gbuffer
    // -----------------------------------------------------------------------------------------------------------------
    glViewport(0, 0, Window::WIDTH, Window::HEIGHT);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glBindFramebuffer(GL_FRAMEBUFFER, gbuffer.gbuffer);
    glClearStencil(0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    CameraPtr currCamera;
    for (auto &camera: cameras) {
        if (camera->active) {
            currCamera = camera;
        }
    }

    shaderGeometryPass.use();
    shaderGeometryPass.uniformMatrix("projection", currCamera->getProjection());
    shaderGeometryPass.uniformMatrix("view", currCamera->getView());

    lightingSystem.draw(shaderGeometryPass);


    for (auto &camera: cameras) {
        glEnable(GL_STENCIL_TEST);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
        glStencilFunc(GL_ALWAYS, (int) camera->ID, -1);
        camera->draw(shaderGeometryPass);
        glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS, 0, -1);
        glDisable(GL_STENCIL_TEST);
    }

    for (auto &pair: models) {
        auto model = pair.second;
        if (std::dynamic_pointer_cast<Terrain>(model)) {
            shaderGeometryPassMountains.use();
            shaderGeometryPassMountains.uniformMatrix("projection", currCamera->getProjection());
            shaderGeometryPassMountains.uniformMatrix("view", currCamera->getView());
            glEnable(GL_STENCIL_TEST);
            glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
            glStencilFunc(GL_ALWAYS, (int) model->ID, -1);
            model->draw(shaderGeometryPassMountains);
            glStencilFunc(GL_NOTEQUAL, (int) model->ID, 0xFF);
            glStencilMask(0x00);


        } else if (std::dynamic_pointer_cast<Model>(model)) {
            if (std::dynamic_pointer_cast<AnimationPoint>(model)) {
                if (std::dynamic_pointer_cast<AnimationPoint>(model)->hide) continue;
            }
            shaderGeometryPass.use();
            glEnable(GL_STENCIL_TEST);
            glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
            glStencilFunc(GL_ALWAYS, (int) model->ID, -1);

            model->draw(shaderGeometryPass);

            glStencilFunc(GL_NOTEQUAL, (int) model->ID, 0xFF);
            glStencilMask(0x00);

        }
        outlineShader.use();
        outlineShader.uniformMatrix("projection", currCamera->getProjection());
        outlineShader.uniformMatrix("view", currCamera->getView());

        if (model->selectionMode) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glLineWidth(10.0f);
            model->draw(outlineShader);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        }
        glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS, 0, -1);
        glDisable(GL_STENCIL_TEST);

    }


    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::renderLighting(CameraPtr &camera, Lighting &lightingSystem) {
    //  lighting pass: calculate lighting by iterating over a screen filled quad pixel-by-pixel using the gbuffer's content.
    // -----------------------------------------------------------------------------------------------------------------
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    shaderLightingPassNew.use();
    shaderLightingPassNew.uniformInt("gPosition", 0);
    shaderLightingPassNew.uniformInt("gNormal", 1);
    shaderLightingPassNew.uniformInt("gDiffuseShininess", 2);
    shaderLightingPassNew.uniformInt("gAmbientSpecular", 3);
    shaderLightingPassNew.uniformInt("depthMap", 4);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gbuffer.gPosition);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gbuffer.gNormal);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, gbuffer.gDiffuseShininess);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, gbuffer.gAmbientSpecular);
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, textureCubeArray.textureCubeArray);

    shaderLightingPassNew.uniformVec3("viewPos", camera->position);
    shaderLightingPassNew.uniformInt("lightsCount", (int) lightingSystem.lights.size());

    shaderLightingPassNew.uniformVec3("sun.direction", lightingSystem.sun.direction);
    shaderLightingPassNew.uniformVec3("sun.color", lightingSystem.sun.color);
    shaderLightingPassNew.uniformBool("sun.enabled", lightingSystem.sun.enabled);

    shaderLightingPassNew.uniformVec3("fog.color", lightingSystem.fog.color);
    shaderLightingPassNew.uniformFloat("fog.density", lightingSystem.fog.density);
    shaderLightingPassNew.uniformBool("fog.enabled", lightingSystem.fog.enabled);

    // finally render quad
    renderQuad();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);

    // copy content of geometry's depth buffer to default framebuffer's depth buffer
    glBindFramebuffer(GL_READ_FRAMEBUFFER, gbuffer.gbuffer);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBlitFramebuffer(0, 0, Window::WIDTH, Window::HEIGHT, 0, 0, Window::WIDTH, Window::HEIGHT, GL_DEPTH_BUFFER_BIT,
                      GL_NEAREST);
    glBlitFramebuffer(0, 0, Window::WIDTH, Window::HEIGHT, 0, 0, Window::WIDTH, Window::HEIGHT, GL_STENCIL_BUFFER_BIT,
                      GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::renderQuad() {

    if (quadVAO == 0) {
        float quadVertices[] = {
                // positions        // texture Coords
                -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
        // setup plane VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);

}

void Renderer::renderSkybox(SkyBox &skybox, CameraPtr &camera, Lighting &lightingSystem) {
    glDepthMask(GL_FALSE);
    glEnable(GL_BLEND);
    glDepthFunc(
            GL_LEQUAL);
    skyboxShader.use();
    glm::mat4 view = glm::mat4(
            glm::mat3(camera->getView()));
    skyboxShader.uniformMatrix("view", view);
    skyboxShader.uniformMatrix("projection", camera->getProjection());

    skyboxShader.uniformBool("sunEnabled", lightingSystem.sun.enabled);
    skyboxShader.uniformBool("fogEnabled", lightingSystem.fog.enabled);
    skyboxShader.uniformVec3("fogColor", lightingSystem.fog.color);
    skybox.draw(skyboxShader);
    glDisable(GL_BLEND);

    glDepthMask(GL_TRUE);
    glDepthFunc(
            GL_LESS);
}

void Renderer::renderCrosshair(AxesCrosshair &crosshair, CameraPtr &camera) {
    AxesCrosshairShader.use();
    AxesCrosshairShader.uniformMatrix("projView", camera->getProjection() * camera->getView());
    AxesCrosshairShader.uniformMatrix("model", glm::translate(glm::mat4(1.0f), camera->position + camera->front) *
                                               glm::scale(glm::mat4(1.0f), glm::vec3(0.03f)));
    crosshair.draw(AxesCrosshairShader);
}
