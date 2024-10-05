//
// Created by korma on 26.02.2024.
//
#include "Window.h"

#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <iostream>



GLFWwindow *Window::window;
int Window::WIDTH;
int Window::HEIGHT;
OPENFILENAME Window::ofn;
char Window::szFile[512] = {0};

int Window::initialize(const char *title) {
    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    // anti-aliasing
//    glfwWindowHint(GLFW_SAMPLES, 4);
    int width, height;
    getDisplayResolution(&width, &height);

    initializeFileSelectionDialog();
    width = (int)(width*0.7);
    height = (int)(height*0.7);
    WIDTH = width;
    HEIGHT = height;
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        Window::terminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0); // Disable VSync

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }
    glViewport(0, 0, width, height);
    return 0;
}

void Window::initializeFileSelectionDialog() {
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "OBJ Files\0*.OBJ\0FBX Files\0*.FBX\0BIN Files\0*.BIN\0All Files\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
}

void Window::terminate() {
    glfwTerminate();
    std::cout << "Terminated GLFW." << std::endl;
}

void Window::getDisplayResolution(int *width, int *height) {
    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    *width = mode->width;
    *height = mode->height;
}

void Window::getWindowSize(int *width, int *height) {
    glfwGetWindowSize(window, width, height);
}

bool Window::isWindowShouldClose() {
    return glfwWindowShouldClose(window);
}

void Window::setWindowShouldClose(bool value) {
    glfwSetWindowShouldClose(window, value);
}

void Window::destroy() {
    glfwDestroyWindow(window);
}

void Window::swapBuffers() {
    glfwSwapBuffers(window);
}

void Window::getCursorPos(double *xpos, double *ypos) {
    glfwGetCursorPos(window, xpos, ypos);
}

std::string Window::openFileSelectionDialog() {
    ofn.lpstrFilter = "All Files\0*.*\0OBJ Files\0*.OBJ\0FBX Files\0*.FBX\0BIN Files\0*.BIN\0";
    if (GetOpenFileName(&ofn) == TRUE) {
        std::string szFileString(szFile);
        std::string currentPath = std::filesystem::current_path().string();

        size_t pos = szFileString.find(currentPath);
        if (pos != std::string::npos) {

            szFileString.erase(pos, currentPath.length()+1);

        }
        std::cout << "File selected: " << szFileString << std::endl;
        return szFileString;
    }
    return "";
}

std::string Window::openFileSaverDialog() {
    ofn.lpstrFilter = "All Files\0*.*\0OBJ Files\0*.OBJ\0FBX Files\0*.FBX\0BIN Files\0*.BIN\0";
    if (GetSaveFileName(&ofn) == TRUE) {
        std::string szFileString(szFile);
        std::string currentPath = std::filesystem::current_path().string();

        size_t pos = szFileString.find(currentPath);
        if (pos != std::string::npos) {

            szFileString.erase(pos, currentPath.length()+1);

        }
        std::cout << "File selected: " << szFileString << std::endl;
        return szFileString;
    }
    return "";
}