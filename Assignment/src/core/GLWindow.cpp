#include "GLWindow.hpp"
#include <iostream>

/**
 * @file GLWindow.cpp
 * @brief Implementation of the GLWindow class for managing an OpenGL window.
 */

namespace graf
{
    /**
     * @brief Static callback function for GLFW keyboard events.
     * 
     * Retrieves the GLWindow instance from the window’s user pointer and forwards
     * the keyboard event to the instance’s registered keyboard callback.
     * 
     * @param window The GLFW window that received the event.
     * @param key The keyboard key that was pressed or released.
     * @param scancode System-specific scancode of the key.
     * @param action The key action (GLFW_PRESS, GLFW_RELEASE, GLFW_REPEAT).
     * @param mods Bit field of modifier keys (e.g., Shift, Ctrl).
     */
    void GLWindow::sKeyboardFunction(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        GLWindow* pWindow = (GLWindow*)glfwGetWindowUserPointer(window);
        pWindow->m_keyboardFunction(key, scancode, action); ///< Forward event to instance callback
    }

    /**
     * @brief Sets the custom keyboard callback function.
     * 
     * Assigns the provided function to handle keyboard events.
     * 
     * @param keyboardFunc The function to be called for keyboard events.
     */
    void GLWindow::SetKeyboardFunction(KeyboardFunction keyboardFunc)
    {
        m_keyboardFunction = keyboardFunc;
    }

    /**
     * @brief Sets the custom close callback function.
     * 
     * Assigns the provided function to be called when the window is closed.
     * 
     * @param function The function to be called when the window is closed.
     */
    void GLWindow::SetCloseFunction(CloseFunction closeFunc)
    {
        m_closeFunction = closeFunc;
    }

    /**
     * @brief Creates and initializes an OpenGL window.
     * 
     * Initializes GLFW, configures an OpenGL 3.3 core profile context, creates a window,
     * loads GLAD, and sets up depth testing and event callbacks.
     * 
     * @param width The width of the window in pixels.
     * @param height The height of the window in pixels.
     * @return 1 on success, -1 if GLFW or GLAD initialization fails.
     */
    int GLWindow::create(unsigned int width, unsigned int height)
    {
        if (!glfwInit())
        {
            glfwTerminate();
            exit(EXIT_FAILURE); ///< Exit if GLFW initialization fails
        }
       
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); ///< Request OpenGL 3.3
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_window = glfwCreateWindow(width, height, "My Title", NULL, NULL);

        glfwMakeContextCurrent(m_window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1; ///< Return failure if GLAD loading fails
        }  

        glEnable(GL_DEPTH_TEST); ///< Enable depth testing for 3D rendering
        glfwSetWindowUserPointer(m_window, this); ///< Store instance pointer for callbacks
        glfwSetKeyCallback(m_window, sKeyboardFunction); ///< Set keyboard callback

        return 1;
    }

    /**
     * @brief Sets the custom rendering callback function.
     * 
     * Assigns the provided function to be called during the render loop.
     * 
     * @param renderFunc The function to be called for rendering each frame.
     */
    void GLWindow::SetRenderFunction(RenderFunction renderFunc)
    {
        m_renderFunction = renderFunc;
    }

    /**
     * @brief Runs the main rendering loop and handles window closure.
     * 
     * Continuously calls the registered render function, swaps buffers, and processes
     * events until the window is closed by the user. Upon closure, calls the registered
     * close function if set.
     */
    void GLWindow::Render()
    {
        while (!glfwWindowShouldClose(m_window))
        {
            m_renderFunction(); ///< Call custom render function
            
            glfwSwapBuffers(m_window); ///< Swap front and back buffers
            glfwPollEvents(); ///< Process pending events (e.g., keyboard, window close)
        }

        if (m_closeFunction) 
            m_closeFunction(); ///< Call the registered close function if it exists

        glfwDestroyWindow(m_window); ///< Destroy the GLFW window
        glfwTerminate(); ///< Terminate GLFW
    }
}