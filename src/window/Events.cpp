//
// Created by korma on 26.02.2024.
//

#include <GLFW/glfw3.h>
#include <cstring>
#include <cstdio>
#include <iostream>
#include "Events.h"

wchar_t* Events::keys;
double Events::mouseX = 0.0;
double Events::mouseY = 0.0;
double Events::mouseDeltaX = 0.0;
double Events::mouseDeltaY = 0.0;
double Events::scrollY = 0;
bool Events::cursorStarted = false;
bool Events::cursorLocked = false;


void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos){
    if(Events::cursorStarted){
        Events::mouseDeltaX = xpos - Events::mouseX;
        Events::mouseDeltaY = ypos - Events::mouseY;
    } else {
        Events::cursorStarted = true;
    }
    Events::mouseX = xpos;
    Events::mouseY = ypos;
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods){
    if(action == GLFW_PRESS){
        Events::keys[GLFW_KEY_LAST + button] = GLFW_PRESS;
    } else if(action == GLFW_RELEASE){
        Events::keys[GLFW_KEY_LAST + button] = GLFW_RELEASE;
    }
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if(action == GLFW_PRESS){
        Events::keys[key] = GLFW_PRESS;
    }else if(action == GLFW_RELEASE){
        Events::keys[key] = GLFW_RELEASE;
    }
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset){
    Events::scrollY = yoffset;
}

void windowSizeCallback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

int Events::initialize(){
    GLFWwindow* window = Window::window;
    Events::keys = new wchar_t[GLFW_KEY_LAST + GLFW_MOUSE_BUTTON_LAST];

    memset(Events::keys, 0, (GLFW_KEY_LAST + GLFW_MOUSE_BUTTON_LAST) * sizeof(wchar_t));

    // callbacks
    glfwSetCursorPosCallback(window, cursorPositionCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetScrollCallback(window, scrollCallback);

    glfwSetWindowSizeCallback(window, windowSizeCallback);

    return 0;
}

void Events::pullEvents(){
    mouseDeltaX = 0.0;
    mouseDeltaY = 0.0;
    scrollY = 0;
    glfwPollEvents();
}

bool Events::keyboardPressed(int key) {
    if(key < 0 || key >= GLFW_KEY_LAST) return false;
    return keys[key];
}

bool Events::keyboardJustPressed(int key) {
    if(key < 0 || key >= GLFW_KEY_LAST) return false;
    if(keys[key] == GLFW_PRESS){
        keys[key] = GLFW_REPEAT;
        return true;
    }
    return false;
}

bool Events::mousePressed(int button) {
    if(button < 0 || button >= GLFW_MOUSE_BUTTON_LAST) return false;
    return keys[button + GLFW_KEY_LAST];
}

bool Events::mouseJustPressed(int button) {
    if(button < 0 || button >= GLFW_MOUSE_BUTTON_LAST) return false;
    if(keys[button + GLFW_KEY_LAST] == GLFW_PRESS){
        keys[button + GLFW_KEY_LAST] = GLFW_REPEAT;
        return true;
    }
    return false;
}
