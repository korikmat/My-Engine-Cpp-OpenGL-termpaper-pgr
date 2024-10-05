#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "window/Window.h"
#include "window/Events.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"
#include "window/Camera.h"
#include "graphics/models/Model.h"
#include "scene/Scene.h"

int fps = 0;
void countFPS() {
    static double previousTime = glfwGetTime();
    static int frameCount = 0;
    double currentTime = glfwGetTime();
    frameCount++;
    if (currentTime - previousTime >= 1.0) {
        fps = frameCount;
        frameCount = 0;
        previousTime = currentTime;
    }
}

int main() {

    Window::initialize("My Engine");
    Events::initialize();
    std::string sceneNameBin = Window::openFileSelectionDialog();
    Scene scene(sceneNameBin);

//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glEnable(GL_CULL_FACE);
    // Enable anti-aliasing
//    glEnable(GL_MULTISAMPLE);
    glDisable((GL_MULTISAMPLE));
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    double previousTime = glfwGetTime();
    float deltaTime;

    while (!Window::isWindowShouldClose()) {
        double currentTime = glfwGetTime();
        deltaTime = (float) (currentTime - previousTime);
        previousTime = currentTime;

        countFPS();
        scene.update(deltaTime);
        scene.draw(fps);

    }
    scene.saveScene();
    Window::destroy();
    Window::terminate();

    return 0;
}
