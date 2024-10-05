//
// Created by korikmat on 07.05.2024.
//

#include "GL/glew.h"
#include "AxesCrosshair.h"
#include "glm/ext/matrix_transform.hpp"


AxesCrosshair::AxesCrosshair() {
    init();
}

void AxesCrosshair::init() {

    glGenVertexArrays(1, &this->vao);
    glGenBuffers(1, &this->vbo_);

    glBindVertexArray(this->vao);

    glBindBuffer(GL_ARRAY_BUFFER, this->vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * lineVertices.size(), &lineVertices[0], GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void AxesCrosshair::draw(Shader &shader) {
    glLineWidth(2.0f);
    glBindVertexArray(this->vao);
    glDrawArrays(GL_LINES, 0, 6);
    glBindVertexArray(0);
    glLineWidth(1.0f);
}