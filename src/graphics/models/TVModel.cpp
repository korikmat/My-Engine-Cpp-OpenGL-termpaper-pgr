//
// Created by korikmat on 19.05.2024.
//

#include "GL/glew.h"
#include <iostream>
#include "TVModel.h"
#include "../../window/Events.h"
#include "GLFW/glfw3.h"
#include "../../hardcode/tv.h"
#include "../../loaders/TextureLoader.h"


TVModel::TVModel(std::string const &path, size_t ID, bool copy) : Model(path, ID, copy),
                                                                  tvScreen("res/tv/tv_screen.obj", ID) {
    createBuffers();
    texture_ = std::make_shared<Texture>("res/tv/tv.001.png");
}

void TVModel::createBuffers() {
    // Create buffer objects/arrays
    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);
    glGenBuffers(1, &ebo_);

    glBindVertexArray(vao_);

    // Load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, tv_n_attribs_per_vertex * tv_n_vertices * sizeof(float), &tv_vertices,
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * tv_n_triangles * sizeof(unsigned), &tv_triangles, GL_STATIC_DRAW);

    // Vertex
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * tv_n_attribs_per_vertex,
                          (void *) (0 * sizeof(float)));

    // Normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * tv_n_attribs_per_vertex,
                          (void *) (3 * sizeof(float)));

    // Texture coordinates
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * tv_n_attribs_per_vertex,
                          (void *) (6 * sizeof(float)));

    glBindVertexArray(0);
}

void TVModel::update() {
    if (isInteracted) {
        tvScreen.channelID = (tvScreen.channelID + 1) % tvScreen.meshes[0]->textures.size();
        isInteracted = false;
    }
    tvScreen.position = position;
    tvScreen.quatRotation = quatRotation;
    tvScreen.cameraDistance = cameraDistance;
    tvScreen.view = view;
    tvScreen.projection = projection;
    tvScreen.scale = scale;
    calculateShadow = false; //TVModel cant work with shadows!
}

void TVModel::draw(Shader &shader) {
    shader.uniformMatrix("model", getModelMatrixQuat());
    shader.uniformInt("texture_diffuse1", 0);
    shader.uniformBool("useDiffTexture", GL_TRUE);
    shader.uniformBool("useSpecTexture", GL_FALSE);
    glActiveTexture(GL_TEXTURE0);

    texture_->bind();
    glBindVertexArray(vao_);

    glDrawElements(GL_TRIANGLES, (GLsizei) tv_n_triangles * 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
    texture_->unbind();
    tvScreen.draw(shader);
}

bool TVModel::isInside(glm::vec3 point) {
    if(glm::length(point - position) < 1.0f) {
        return true;
    }
    return false;
}