//
// Created by korikmat on 07.05.2024.
//

#include <iostream>
#include "TextureLoader.h"
#include "IL/il.h"

bool TextureLoader::loadTexImage2D(const char *fileName, GLenum target) {
    // DevIL library has to be initialized (ilInit() must be called)
    ilInit();
    // DevIL uses mechanism similar to OpenGL, each image has its ID (name)
    ILuint img_id;
    ilGenImages(1, &img_id); // generate one image ID (name)
    ilBindImage(img_id); // bind that generated id

    // set origin to LOWER LEFT corner (the orientation which OpenGL uses)
    ilEnable(IL_ORIGIN_SET);
    ilSetInteger(IL_ORIGIN_MODE, IL_ORIGIN_LOWER_LEFT);

    // this will load image data to the currently bound image
    if (ilLoadImage(fileName) == IL_FALSE) {
        ilDeleteImages(1, &img_id);
        std::cerr << __FUNCTION__ << " cannot load image " << fileName << std::endl;
        return false;
    }
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

    // if the image was correctly loaded, we can obtain some informatins about our image
    ILint width = ilGetInteger(IL_IMAGE_WIDTH);
    ILint height = ilGetInteger(IL_IMAGE_HEIGHT);
//    ILenum format = ilGetInteger(IL_IMAGE_FORMAT);


    // bogus ATI drivers may require this call to work with mipmaps
    //glEnable(GL_TEXTURE_2D);
    ILubyte *data = ilGetData();
    glTexImage2D(target, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid *) data);
    // free our data (they were copied to OpenGL)
    ilDeleteImages(1, &img_id);

    return true;
}

GLuint TextureLoader::createTexture(const char *fileName, int *width, int *height) {
    // generate and bind one texture
    GLuint tex = 0;
    glGenTextures(1, &tex);

    glBindTexture(GL_TEXTURE_2D, tex);

    // set linear filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR); // TODO: check if this is correct
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER); // TextureType does not repeat
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER); // TextureType does not repeat

    // upload our image data to OpenGL
    if (!loadTexImage2D(fileName, GL_TEXTURE_2D)) {
        glBindTexture(GL_TEXTURE_2D, 0);
        glDeleteTextures(1, &tex);
        return 0;
    }

    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, width);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, height);
//    // create mipmaps
//    if(mipmap)
    glGenerateMipmap(GL_TEXTURE_2D);
    // unbind the texture (just in case someone will mess up with texture calls later)
    glBindTexture(GL_TEXTURE_2D, 0);
//    CHECK_GL_ERROR();
    return tex;
}

GLuint TextureLoader::createSkyBoxTexture(const std::vector<std::string> &facesPaths, int *width, int *height) {
    // generate and bind one texture
    GLuint tex = 0;
    glGenTextures(1, &tex);

    glBindTexture(GL_TEXTURE_CUBE_MAP, tex);

    // set linear filtering
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    // upload our image data to OpenGL
    for (size_t i = 0; i < facesPaths.size(); i++) {
        if (!loadTexImage2D(facesPaths[i].c_str(), GL_TEXTURE_CUBE_MAP_POSITIVE_X + i)) {
            glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
            glDeleteTextures(1, &tex);
            return 0;
        }
    }

    glGetTexLevelParameteriv(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_TEXTURE_WIDTH, width);
    glGetTexLevelParameteriv(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_TEXTURE_HEIGHT, height);
//    // create mipmaps
//    if(mipmap)
//        glGenerateMipmap(GL_TEXTURE_2D);
    // unbind the texture (just in case someone will mess up with texture calls later)
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
//    CHECK_GL_ERROR();
    return tex;
}

unsigned int TextureLoader::loadBasicTexture(const char *path, int *width, int *height) {
    GLuint id = createTexture(path, width, height);
    if (id == 0) {
        std::cerr << "Failed to load texture: " << path << std::endl;
        return 0;
    }

    std::cout << "Loaded texture: " << path << " (" << *width << "x" << *height << ")" << std::endl;

    return id;
}

unsigned int TextureLoader::loadSkyBoxTexture(std::vector<std::string> facesPaths, int *width, int *height) {
    std::cout << "Loading skybox texture: " << facesPaths[0] << std::endl;
    GLuint id = createSkyBoxTexture(facesPaths, width, height);
    if (id == 0) {
        std::cerr << "Failed to load texture: " << facesPaths[0] << std::endl;
        return 0;
    }
    std::cout << "Loaded skybox texture: " << facesPaths[0] << " (" << *width << "x" << *height << ")" << std::endl;

    return id;
}