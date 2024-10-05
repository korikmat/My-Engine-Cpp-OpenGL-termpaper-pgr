//
// Created by korikmat on 07.05.2024.
//

#include "SkyBox.h"
#include "GL/glew.h"

SkyBox::SkyBox() : texture(facesPaths) {
    init();
}

void SkyBox::init() {
    glGenVertexArrays(1, &this->vao);
    glGenBuffers(1, &this->vbo_);
    glBindVertexArray(this->vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo_);
    glBufferData(GL_ARRAY_BUFFER, (sizeof(float)) * skyboxVertices.size(), &skyboxVertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);

    glBindVertexArray(0);
}

void SkyBox::draw(Shader &shader) {
    shader.use();
    shader.uniformInt("skybox", 0);

    glBindVertexArray(vao);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->texture.id);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}