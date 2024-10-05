//
// Created by korikmat on 15.05.2024.
//
#include <iostream>
#include "TVScreen.h"
#include "glm/ext/matrix_transform.hpp"

TVScreen::TVScreen(std::string const &path, size_t ID, bool copy) : Model(path, ID, copy) {
    meshes[0]->textures.push_back(std::make_shared<Texture>("res/tv/spritesheet(4).png"));
    meshes[0]->textures.push_back(std::make_shared<Texture>("res/tv/spritesheet(5).png"));
    meshes[0]->textures.push_back(std::make_shared<Texture>("res/tv/spritesheet(6).png"));
    meshes[0]->textures.push_back(std::make_shared<Texture>("res/tv/spritesheet(7).png"));
    meshes[0]->textures.push_back(std::make_shared<Texture>("res/tv/spritesheet(8).png"));
    meshes[0]->textures.push_back(std::make_shared<Texture>("res/tv/hypnosis.jpg"));
}

void TVScreen::draw(Shader &shader) {
    this->shader.use();
    this->shader.uniformMatrix("projection", projection);
    this->shader.uniformMatrix("view", view);
    this->shader.uniformMatrix("model", getModelMatrixQuat());
    for (auto &mesh: meshes) {
        mesh->drawTvScreen(this->shader, channelID);
    }
}
