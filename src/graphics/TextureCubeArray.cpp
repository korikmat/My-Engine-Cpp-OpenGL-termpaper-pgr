//
// Created by korikmat on 12.05.2024.
//

#include "GL/glew.h"
#include "TextureCubeArray.h"


TextureCubeArray::TextureCubeArray(unsigned int levels) {
    // generate texture
    glGenFramebuffers(1, &depthMapFBO);


    glGenTextures(1, &textureCubeArray);
    glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, textureCubeArray);
    glTexImage3D(
        GL_TEXTURE_CUBE_MAP_ARRAY, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 6*levels, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);

    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // bind texture to framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glDrawBuffers(0, 0);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, textureCubeArray, 0);

    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void TextureCubeArray::bind() {
    glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, textureCubeArray);
}
