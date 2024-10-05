/// @file Window.h
/// @brief This file contains the definition of the Window class.
///
/// Created by korma on 26.02.2024.

#ifndef PROJECT_WINDOW_H
#define PROJECT_WINDOW_H

#include <string>
#include <filesystem>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

class GLFWwindow;

/// @class Window
/// @brief The Window class handles the creation and management of the application window.
/// @details This class provides methods to initialize, terminate, and manage window properties and events.
class Window {
public:
    /// @brief The width of the window.
    static int WIDTH;

    /// @brief The height of the window.
    static int HEIGHT;

    /// @brief Pointer to the GLFW window object.
    static GLFWwindow *window;

    #if defined(_WIN32) || defined(_WIN64)
    /// @brief Open file name structure for file dialogs (Windows only).
    static OPENFILENAME ofn;

    /// @brief Buffer for storing file paths in file dialogs.
    static char szFile[512];
    #endif

    /// @brief Initializes the window with the specified title.
    /// @param title The title of the window.
    /// @return An integer representing the success or failure of the initialization.
    static int initialize(const char *title);

    /// @brief Terminates the window and cleans up resources.
    static void terminate();

    /// @brief Gets the display resolution.
    /// @param width Pointer to an integer to store the display width.
    /// @param height Pointer to an integer to store the display height.
    static void getDisplayResolution(int *width, int *height);

    /// @brief Gets the window size.
    /// @param width Pointer to an integer to store the window width.
    /// @param height Pointer to an integer to store the window height.
    static void getWindowSize(int *width, int *height);

    /// @brief Checks if the window should close.
    /// @return True if the window should close, false otherwise.
    static bool isWindowShouldClose();

    /// @brief Sets whether the window should close.
    /// @param value True to close the window, false otherwise.
    static void setWindowShouldClose(bool value);

    /// @brief Destroys the window.
    static void destroy();

    /// @brief Swaps the front and back buffers.
    static void swapBuffers();

    /// @brief Gets the current cursor position.
    /// @param xpos Pointer to a double to store the x position of the cursor.
    /// @param ypos Pointer to a double to store the y position of the cursor.
    static void getCursorPos(double *xpos, double *ypos);

    /// @brief Opens a file selection dialog and returns the selected file path.
    /// @return The selected file path as a string.
    static std::string openFileSelectionDialog();

    /// @brief Opens a file saver dialog and returns the selected file path.
    /// @return The selected file path as a string.
    static std::string openFileSaverDialog();

private:
    /// @brief Initializes the file selection dialog (Windows only).
    static void initializeFileSelectionDialog();
};

#endif //PROJECT_WINDOW_H
