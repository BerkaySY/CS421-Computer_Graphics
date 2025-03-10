#include "VertexBuffer.hpp"
#include "Exceptions.hpp"
#include "ErrorCheck.hpp"
#include <glad/glad.h>

/**
 * @file VertexBuffer.cpp
 * @brief Implementation of the VertexBuffer class for managing OpenGL vertex buffers.
 */

namespace graf
{
    /**
     * @brief Creates an OpenGL vertex buffer with the specified data.
     * 
     * Generates a vertex buffer object, binds it, and uploads the provided vertex data
     * to the GPU with a static draw hint.
     * 
     * @param data Pointer to the vertex data (e.g., positions, texture coords).
     * @param size Size of the data in bytes.
     * @exception BufferException Thrown if data is null, size is invalid, or buffer creation fails.
     */
    void VertexBuffer::Create(const void* data, int size)
    {
        if (data == nullptr || size <= 0)
            throw BufferException("Invalid vertex buffer data or size"); ///< Validate input

        glGenBuffers(1, &m_id); ///< Generate buffer ID
        if (m_id == 0)
            throw BufferException("Failed to generate vertex buffer"); ///< Check generation success

        glBindBuffer(GL_ARRAY_BUFFER, m_id); ///< Bind buffer to GL_ARRAY_BUFFER target
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW); ///< Upload data to GPU

        CheckGLError("Vertex Buffer Creation"); ///< Check for OpenGL errors
    }

    /**
     * @brief Binds the vertex buffer for use in rendering.
     * 
     * Activates this vertex buffer in the OpenGL context by binding it to the
     * GL_ARRAY_BUFFER target.
     */
    void VertexBuffer::Bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
    }

    /**
     * @brief Unbinds the vertex buffer.
     * 
     * Removes this vertex buffer from the active OpenGL context by binding 0 to the
     * GL_ARRAY_BUFFER target.
     */
    void VertexBuffer::Unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }    

    /**
     * @brief Releases the vertex buffer’s OpenGL resources.
     * 
     * Deletes the buffer object from OpenGL memory and resets the handle if it exists.
     */
    void VertexBuffer::Release()
    {
        if (m_id != 0) 
        {
            glDeleteBuffers(1, &m_id); ///< Free GPU memory
            m_id = 0;                  ///< Reset handle to indicate deletion
        }
    }
}