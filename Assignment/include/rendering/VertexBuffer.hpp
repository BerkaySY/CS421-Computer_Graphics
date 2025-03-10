#pragma once

/**
 * @file VertexBuffer.hpp
 * @brief Defines the VertexBuffer class for managing OpenGL vertex buffers.
 */

namespace graf
{
    /**
     * @class VertexBuffer
     * @brief A class for handling OpenGL vertex buffer objects (VBOs).
     * 
     * This class encapsulates the creation, binding, and management of a vertex buffer,
     * which stores vertex data (e.g., positions, texture coordinates) for 3D rendering.
     */
    class VertexBuffer
    {
    public:
        /**
         * @brief Creates an OpenGL vertex buffer with the specified data.
         * 
         * Allocates and initializes a vertex buffer object with the provided vertex data.
         * 
         * @param data Pointer to the vertex data.
         * @param size Size of the data in bytes.
         * @exception BufferException Thrown if data is null, size is invalid, or buffer creation fails.
         */
        void Create(const void* data, int size);

        /**
         * @brief Binds the vertex buffer for use in rendering.
         * 
         * Makes this vertex buffer the active one in the OpenGL context.
         */
        void Bind();

        /**
         * @brief Unbinds the vertex buffer.
         * 
         * Removes this vertex buffer from the active OpenGL context.
         */
        void Unbind();

        /**
         * @brief Releases the vertex buffer’s OpenGL resources.
         * 
         * Deletes the buffer object from OpenGL memory if it exists.
         */
        void Release();

    private:
        unsigned int m_id; ///< OpenGL handle for the vertex buffer object.
    };
}