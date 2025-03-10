#pragma once

#include <functional>

/**
 * @file FunctionTypes.hpp
 * @brief Defines function type aliases for callbacks.
 */

namespace graf
{
    using namespace std;

    /**
     * @brief Alias for a rendering callback function.
     * 
     * Represents a function that takes no parameters and returns void.
     * Used as a callback for custom rendering logic in the GLWindow class.
     */
    using RenderFunction = function<void()>;

    /**
     * @brief Alias for a keyboard event callback function.
     * 
     * Represents a function that takes three integer parameters and returns void.
     * Used as a callback for handling keyboard events in the GLWindow class.
     * 
     * @param key The keyboard key that was pressed or released.
     * @param scancode System-specific scancode of the key.
     * @param action The key action (e.g., press, release, repeat).
     */
    using KeyboardFunction = function<void(int, int, int)>;

    /**
     * @brief Alias for a close event callback function.
     * 
     * Represents a function that takes no parameters and returns void.
     * Used as a callback for handling window close events in the GLWindow class.
     */
    using CloseFunction     = function<void()>;
}