//
// Created by korikmat on 12.05.2024.
//
#include "GL/glew.h"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

#include <cstring>
#include <memory>
#include <random>
#include <iostream>

#include "Lighting.h"


Lighting::Lighting() {
    createUBO();
    memset(lightsData, 0, sizeof(LightData) * MAX_LIGHTS);
    update();

    sun.direction = glm::vec3(1.0f, -1.0f, 1.0f);
    sun.color = glm::vec3(1.0f, 1.0f, 1.0f);
    sun.enabled = true;

}

void Lighting::createUBO() {
    glGenBuffers(1, &ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(LightData) * MAX_LIGHTS, 0, GL_STATIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

}

void Lighting::addPointLight(size_t ID, glm::vec3 position, glm::vec3 color) {
    auto light = std::make_shared<Light>(ID, position, color);
    add(light);
}

void Lighting::addSpotLight(size_t ID, glm::vec3 position, glm::vec3 color, glm::vec4 direction_angle) {
    auto light = std::make_shared<Light>(ID, position, color, direction_angle);
    add(light);
}

void Lighting::update() {

    for (int i = 0; i < (int)lights.size(); i++) {
        //TODO update only changed lights
        lightsData[i].position = lights[i]->position;
        lightsData[i].color = lights[i]->color;
        lightsData[i].attenuation.r = lights[i]->radius; // radius
        lightsData[i].attenuation[1] = 4.5f / lights[i]->radius; // linear attenuation
        lightsData[i].attenuation[2] =
                4 * lightsData[i].attenuation[1] * lightsData[i].attenuation[1]; // quadratic attenuation

        lightsData[i].direction_angle = lights[i]->direction_angle;
        recalcVP(i);

    }


    glBindBuffer(GL_UNIFORM_BUFFER, ubo);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(LightData) * MAX_LIGHTS, lightsData);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

}

void Lighting::recalcVP(int idx) {
    //TODO: recalc only changed lights
    glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), 1.0f, lights[idx]->near_plane, lights[idx]->radius);
    lightsData[idx].vp[0] = shadowProj *
                            glm::lookAt(lights[idx]->position, lights[idx]->position + glm::vec3(1.0f, 0.0f, 0.0f),
                                        glm::vec3(0.0f, -1.0f, 0.0f));
    lightsData[idx].vp[1] = shadowProj *
                            glm::lookAt(lights[idx]->position, lights[idx]->position + glm::vec3(-1.0f, 0.0f, 0.0f),
                                        glm::vec3(0.0f, -1.0f, 0.0f));
    lightsData[idx].vp[2] = shadowProj *
                            glm::lookAt(lights[idx]->position, lights[idx]->position + glm::vec3(0.0f, 1.0f, 0.0f),
                                        glm::vec3(0.0f, 0.0f, 1.0f));
    lightsData[idx].vp[3] = shadowProj *
                            glm::lookAt(lights[idx]->position, lights[idx]->position + glm::vec3(0.0f, -1.0f, 0.0f),
                                        glm::vec3(0.0f, 0.0f, -1.0f));
    lightsData[idx].vp[4] = shadowProj *
                            glm::lookAt(lights[idx]->position, lights[idx]->position + glm::vec3(0.0f, 0.0f, 1.0f),
                                        glm::vec3(0.0f, -1.0f, 0.0f));
    lightsData[idx].vp[5] = shadowProj *
                            glm::lookAt(lights[idx]->position, lights[idx]->position + glm::vec3(0.0f, 0.0f, -1.0f),
                                        glm::vec3(0.0f, -1.0f, 0.0f));
}

void Lighting::draw(Shader &shader) {
    for (auto &light: lights) {
        shader.uniformMatrix("model", glm::scale(glm::translate(glm::mat4(1.0f), light->position), glm::vec3(0.04f)));

        glEnable(GL_STENCIL_TEST);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
        glStencilFunc(GL_ALWAYS, light->ID, -1);
        light->draw(shader);
        glStencilFunc(GL_ALWAYS, 0, -1);
        glDisable(GL_STENCIL_TEST);
    }
}

float Lighting::getRandomColor() {
    static std::random_device rd;
    static std::mt19937 generator(rd());
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return (float) distribution(generator);
}

void Lighting::add(const LightPtr &light) {
    if (lights.size() >= MAX_LIGHTS) {
        std::cout << "\nMax lights count reached\n" << std::endl;
        return;
    }

    lights.push_back(light);
    update();
}