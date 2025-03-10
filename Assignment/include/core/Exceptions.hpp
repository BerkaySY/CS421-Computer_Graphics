#pragma once

#include <stdexcept>
#include <string>

/**
 * @file Exceptions.hpp
 * @brief Defines exception classes for error handling.
 */

namespace graf 
{
    /**
     * @class GrafException
     * @brief Base exception class for general errors.
     * 
     * This class inherits from std::runtime_error and serves as the parent for
     * all specific exception types used in the library.
     */
    class GrafException : public std::runtime_error 
    {
    public:
        /**
         * @brief Constructs a GrafException with a custom message.
         * @param message The error message describing the exception.
         */
        explicit GrafException(const std::string& message) : std::runtime_error(message) {}
    };

    /**
     * @class ShaderException
     * @brief Exception class for shader-related errors.
     * 
     * Thrown when an error occurs during shader creation, compilation, or linking.
     */
    class ShaderException : public GrafException 
    {
    public:
        /**
         * @brief Constructs a ShaderException with a detailed message.
         * @param message The specific error message (prefixed with "Shader Error: ").
         */
        explicit ShaderException(const std::string& message) : GrafException("Shader Error: " + message) {}
    };

    /**
     * @class TextureException
     * @brief Exception class for texture-related errors.
     * 
     * Thrown when an error occurs during texture loading or binding.
     */
    class TextureException : public GrafException 
    {
    public:
        /**
         * @brief Constructs a TextureException with a detailed message.
         * @param message The specific error message (prefixed with "Texture Error: ").
         */
        explicit TextureException(const std::string& message) : GrafException("Texture Error: " + message) {}
    };

    /**
     * @class BufferException
     * @brief Exception class for buffer-related errors.
     * 
     * Thrown when an error occurs during vertex or index buffer creation or binding.
     */
    class BufferException : public GrafException 
    {
    public:
        /**
         * @brief Constructs a BufferException with a detailed message.
         * @param message The specific error message (prefixed with "Buffer Error: ").
         */
        explicit BufferException(const std::string& message) : GrafException("Buffer Error: " + message) {}
    };

    /**
     * @class GLWindowException
     * @brief Exception class for window-related errors.
     * 
     * Thrown when an error occurs during OpenGL window creation or management.
     */
    class GLWindowException : public GrafException 
    {
    public:
        /**
         * @brief Constructs a GLWindowException with a detailed message.
         * @param message The specific error message (prefixed with "Window Error: ").
         */
        explicit GLWindowException(const std::string& message) : GrafException("Window Error: " + message) {}
    };
}