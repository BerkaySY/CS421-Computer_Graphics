#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "FunctionTypes.hpp"

/**
 * @file GLWindow.hpp
 * @brief Defines the GLWindow class for managing an OpenGL window.
 */

namespace graf
{
    /**
     * @class GLWindow
     * @brief A class for creating and managing an OpenGL window using GLFW.
     * 
     * This class encapsulates the creation, rendering, and event handling of an OpenGL
     * window. It supports custom rendering and keyboard input callbacks through function objects.
     */
    class GLWindow
    {
    public:
        /**
         * @brief Creates and initializes an OpenGL window.
         * 
         * Initializes GLFW, sets up an OpenGL context, and creates a window with the
         * specified dimensions.
         * 
         * @param width The width of the window in pixels.
         * @param height The height of the window in pixels.
         * @return 1 on success, -1 on failure (e.g., GLFW or GLAD initialization fails).
         * @exception GLWindowException Thrown if window creation fails (not directly here, but in practice).
         */
        int create(unsigned int width, unsigned int height);

        /**
         * @brief Runs the main rendering loop.
         * 
         * Enters a loop that continuously calls the render function, swaps buffers,
         * and processes events until the window is closed.
         */
        void Render();

        /**
         * @brief Sets the custom rendering callback function.
         * @param renderFunc The function to be called for rendering each frame.
         */
        void SetRenderFunction(RenderFunction renderFunc);

        /**
         * @brief Sets the custom keyboard callback function.
         * @param keyboardFunc The function to be called for keyboard events.
         */
        void SetKeyboardFunction(KeyboardFunction keyboardFunc);

        /**
         * @brief Sets the custom close event callback function.
         * @param closeFunc The function to be called when the window is closed.
         */
        void SetCloseFunction(CloseFunction closeFunc);

    private:
        /**
         * @brief Static callback function for GLFW keyboard events.
         * 
         * Forwards keyboard events to the instance’s keyboard function.
         * 
         * @param window The GLFW window that received the event.
         * @param key The keyboard key that was pressed or released.
         * @param scancode System-specific scancode of the key.
         * @param action The key action (GLFW_PRESS, GLFW_RELEASE, GLFW_REPEAT).
         * @param mods Bit field of modifier keys (e.g., Shift, Ctrl).
         */
        static void sKeyboardFunction(GLFWwindow* window, int key, int scancode, int action, int mods);
    
    private:
        GLFWwindow*         m_window;           ///< Pointer to the GLFW window object.
        RenderFunction      m_renderFunction;   ///< Callback function for rendering.
        KeyboardFunction    m_keyboardFunction; ///< Callback function for keyboard events.
        CloseFunction       m_closeFunction;    ///< Callback function for window close events.
    };
}