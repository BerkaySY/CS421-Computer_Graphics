#pragma once

#include <glad/glad.h>
#include "Exceptions.hpp"
#include <string>

/**
 * @file ErrorCheck.hpp
 * @brief Provides utility functions for OpenGL error checking.
 */

namespace graf 
{
    /**
     * @brief Checks for OpenGL errors and throws an exception if one occurs.
     * 
     * This inline function queries the current OpenGL error state using glGetError()
     * and converts the error code into a human-readable message. If an error is detected,
     * it throws a GrafException with details about the failed operation.
     * 
     * @param operation A string describing the OpenGL operation being checked (e.g., "Vertex Buffer Creation").
     * @exception GrafException Thrown if an OpenGL error is detected, containing the operation and error message.
     */
    inline void CheckGLError(const std::string& operation) 
    {
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) 
        {
            std::string errorMsg; ///< The human-readable error message
            switch (error) 
            {
                case GL_INVALID_ENUM:       errorMsg = "Invalid enum";      break; ///< An enum parameter is invalid
                case GL_INVALID_VALUE:      errorMsg = "Invalid value";     break; ///< A numeric value is out of range
                case GL_INVALID_OPERATION:  errorMsg = "Invalid operation"; break; ///< The operation is not allowed in the current state
                case GL_OUT_OF_MEMORY:      errorMsg = "Out of memory";     break; ///< Insufficient memory to complete the operation
                default:                    errorMsg = "Unknown error";     break; ///< An unrecognized error code
            }
            throw GrafException(operation + " failed: " + errorMsg);
        }
    }
}