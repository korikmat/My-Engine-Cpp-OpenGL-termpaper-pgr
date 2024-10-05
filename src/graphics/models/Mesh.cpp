//
// Created by korikmat on 30.03.2024.
//

#include "Mesh.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/gtx/transform.hpp"

#include <utility>
#include <iostream>

Mesh::Mesh(std::vector<VertexType> vertices, std::vector<unsigned int> indices, std::vector<TexturePtr> textures,
           Materials materials)
        : vertices(std::move(vertices)), indices(std::move(indices)), textures(std::move(textures)),
          materials(std::move(materials)) {
    init();
}

Mesh::Mesh(const float *buffer, size_t vertices, const int *attrs) : verticesCount(vertices) {
    vertexSize = 0;
    for (int i = 0; attrs[i]; i++) {
        vertexSize += attrs[i];
    }

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo_);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    if (buffer) {
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexSize * vertices, buffer, GL_STATIC_DRAW);
    } else {
        glBufferData(GL_ARRAY_BUFFER, 0, {}, GL_STATIC_DRAW);
    }


    // attributes
    int offset = 0;
    for (int i = 0; attrs[i]; i++) {
        int size = attrs[i];
        glVertexAttribPointer(i, size, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float),
                              (GLvoid *) (offset * sizeof(float)));
        glEnableVertexAttribArray(i);
        offset += size;
    }

    glBindVertexArray(0);
}


void Mesh::init() {
    // Create buffers/arrays
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo_);
    glGenBuffers(1, &ebo_);

    glBindVertexArray(vao);

    // Load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexType), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);


    // Vertex coordinates
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexType), (void *) 0);

    // Normal coordinates
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexType), (void *) offsetof(VertexType, normal));

    // Texture coordinates
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexType), (void *) offsetof(VertexType, tex_coords));

    // vector of tangents
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexType), (void *) offsetof(VertexType, tangent));

    // vector of bitangents
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(VertexType), (void *) offsetof(VertexType, bitangent));

    glBindVertexArray(0);

}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo_);
    glDeleteBuffers(1, &ebo_);
}

void Mesh::draw(Shader &shader) {
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        std::string number;
        std::string name = textures[i]->type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++);
        else if (name == "texture_normal")
            number = std::to_string(normalNr++);
        else if (name == "texture_height")
            number = std::to_string(heightNr++);
        shader.uniformInt((name + number).c_str(), i);
        textures[i]->bind();
    }
    shader.uniformVec4("material.diffuse", materials.diffuse);
    shader.uniformVec4("material.specular", materials.specular);
    shader.uniformFloat("material.shininess", materials.shininess);

    shader.uniformBool("useDiffTexture", hasDiffTexture);
    shader.uniformBool("useSpecTexture", hasSpecTexture);

    // draw mesh
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, (GLsizei) indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);

    // unbing all textures
    for (auto &texture: textures) {
        texture->unbind();
    }

}

static double previousTime = glfwGetTime();
static int frameCount = 0;

static float angle = 0.0f;


void Mesh::drawTvScreen(Shader &shader, int channelID) {

    if (!textures.empty()) {
        shader.uniformInt("texture_diffuse1", 0);
        textures[channelID]->bind();
    }

    double currentTime = glfwGetTime();

    if (currentTime - previousTime >= FRAMES_PERIOD_SEC) {
        frameCount++;
        previousTime = currentTime;
    }
    if (frameCount > FRAMES_COUNT) {
        frameCount = 0;
    }
    shader.uniformVec2("texOffset", glm::vec2((float) (frameCount % 7) / 7, (float) -(frameCount / 7) / 7));
    shader.uniformMat3("textureMatrix", glm::mat3(1.0f));
    if(channelID == HYPNOSIS) { // hypnosis
        shader.uniformVec2("texOffset", glm::vec2((float) (HYPNOSIS_FRAME % FRAMES_COLUMN) / FRAMES_COLUMN, (float) -(HYPNOSIS_FRAME / FRAMES_COLUMN) / FRAMES_ROW)); // translation to the center

        angle+=0.1f;
        float cosAngle = cos(glm::radians((float)angle));
        float sinAngle = sin(glm::radians((float)angle));
        glm::mat3 rotationMatrix(1.0f);
        rotationMatrix[0][0] = cosAngle;
        rotationMatrix[0][1] = sinAngle;
        rotationMatrix[1][0] = -sinAngle;
        rotationMatrix[1][1] = cosAngle;

        shader.uniformMat3("textureMatrix", rotationMatrix);

    }

    shader.uniformVec4("material.diffuse", materials.diffuse);
    shader.uniformVec4("material.specular", materials.specular);
    shader.uniformFloat("material.shininess", materials.shininess);

    shader.uniformBool("useDiffTexture", hasDiffTexture);
    shader.uniformBool("useSpecTexture", hasSpecTexture);



    // Draw mesh
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, (GLsizei) indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);

    // Unbind all textures
    for (auto &texture: textures) {
        texture->unbind();
    }


}

void Mesh::drawUi() {
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, verticesCount);
    glBindVertexArray(0);
}

void Mesh::reload(const float *buffer, size_t verticesCount) {
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexSize * verticesCount, buffer, GL_STATIC_DRAW);
    this->verticesCount = verticesCount;
}