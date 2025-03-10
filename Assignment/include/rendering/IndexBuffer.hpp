#pragma once

/**
 * @file IndexBuffer.hpp
 * @brief Defines the IndexBuffer class for managing OpenGL index buffers.
 */

namespace graf
{
    /**
     * @class IndexBuffer
     * @brief A class for handling OpenGL index buffer objects (IBOs).
     * 
     * This class encapsulates the creation, binding, and management of an index buffer,
     * which stores indices defining the order of vertices to form triangles in 3D rendering.
     */
    class IndexBuffer
    {
    public:
        /**
         * @brief Creates an OpenGL index buffer with the specified data.
         * 
         * Allocates and initializes an index buffer object with the provided index data.
         * 
         * @param data Pointer to the index data (unsigned integers).
         * @param size Size of the data in bytes.
         * @exception BufferException Thrown if data is null, size is invalid, or buffer creation fails.
         */
        void Create(const void* data, int size);

        /**
         * @brief Binds the index buffer for use in rendering.
         * 
         * Makes this index buffer the active one in the OpenGL context.
         */
        void Bind();

        /**
         * @brief Unbinds the index buffer.
         * 
         * Removes this index buffer from the active OpenGL context.
         */
        void Unbind();

        /**
         * @brief Releases the index buffer’s OpenGL resources.
         * 
         * Deletes the buffer object from OpenGL memory if it exists.
         */
        void Release();

        /**
         * @brief Gets the number of indices in the buffer.
         * @return The number of indices stored in the buffer.
         */
        int getIndexCount() const;

    private:
        unsigned int m_id;        ///< OpenGL handle for the index buffer object.
        int m_IndexCount;         ///< Number of indices in the buffer.
    };
}