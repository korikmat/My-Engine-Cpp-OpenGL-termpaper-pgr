//
// Created by korikmat on 11.05.2024.
//

#include <iostream>
#include "gBuffer.h"
#include "GL/glew.h"
#include "../window/Window.h"

gBuffer::gBuffer() {
    // configure g-buffer framebuffer
    // ------------------------------
    glGenFramebuffers(1, &gbuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, gbuffer);
    // position color buffer
    glGenTextures(1, &gPosition);
    glBindTexture(GL_TEXTURE_2D, gPosition);
                                    // GL_RGB16F non enough for smooth lighting!
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, Window::WIDTH, Window::HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);
    // normal color buffer
    glGenTextures(1, &gNormal);
    glBindTexture(GL_TEXTURE_2D, gNormal);
    // TODO Maybe GL_RGB16F enough!
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, Window::WIDTH, Window::HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);
    // diffuse + shininess color buffer
    glGenTextures(1, &gDiffuseShininess);
    glBindTexture(GL_TEXTURE_2D, gDiffuseShininess);
    // TODO Maybe GL_RGBA16F enough!
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, Window::WIDTH, Window::HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gDiffuseShininess, 0);

    // specular color buffer
    glGenTextures(1, &gAmbientSpecular);
    glBindTexture(GL_TEXTURE_2D, gAmbientSpecular);
    // TODO Maybe GL_RGBA16F enough!
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, Window::WIDTH, Window::HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, gAmbientSpecular, 0);


    // tell OpenGL which color attachments we'll use for rendering
    glDrawBuffers(4, attachments);
    // create and attach depth buffer (renderbuffer)
    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Window::WIDTH, Window::HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboDepth);

    // finally check if framebuffer is complete
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Framebuffer not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}