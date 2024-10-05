/// @file Events.h
/// @brief This file contains the definition of the Events class.
///
/// Created by korma on 26.02.2024.

#ifndef PROJECT_EVENTS_H
#define PROJECT_EVENTS_H

#include "Window.h"

/// @class Events
/// @brief The Events class handles input events such as keyboard and mouse actions.
/// @details This class provides methods to initialize event handling, pull events, and check the state of keyboard and mouse inputs.
class Events {
public:
    /// @brief Array of key states.
    static wchar_t* keys;

    /// @brief The current X position of the mouse.
    static double mouseX;

    /// @brief The current Y position of the mouse.
    static double mouseY;

    /// @brief The change in X position of the mouse since the last frame.
    static double mouseDeltaX;

    /// @brief The change in Y position of the mouse since the last frame.
    static double mouseDeltaY;

    /// @brief The scroll amount in the Y direction.
    static double scrollY;

    /// @brief Flag indicating whether the cursor has started.
    static bool cursorStarted;

    /// @brief Flag indicating whether the cursor is locked.
    static bool cursorLocked;

    /// @brief Initializes the event handling system.
    /// @return An integer representing the success or failure of the initialization.
    static int initialize();

    /// @brief Polls for events and updates the state of input devices.
    static void pullEvents();

    /// @brief Checks if a keyboard key is currently pressed.
    /// @param key The key to check.
    /// @return True if the key is pressed, false otherwise.
    static bool keyboardPressed(int key);

    /// @brief Checks if a mouse button is currently pressed.
    /// @param button The mouse button to check.
    /// @return True if the mouse button is pressed, false otherwise.
    static bool mousePressed(int button);

    /// @brief Checks if a keyboard key was just pressed.
    /// @param key The key to check.
    /// @return True if the key was just pressed, false otherwise.
    static bool keyboardJustPressed(int key);

    /// @brief Checks if a mouse button was just pressed.
    /// @param button The mouse button to check.
    /// @return True if the mouse button was just pressed, false otherwise.
    static bool mouseJustPressed(int button);
};

#endif //PROJECT_EVENTS_H
