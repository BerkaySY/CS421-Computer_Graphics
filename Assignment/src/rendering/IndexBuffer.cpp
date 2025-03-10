#include "Indexbuffer.hpp"
#include "Exceptions.hpp"
#include "ErrorCheck.hpp"
#include <glad/glad.h>

/**
 * @file IndexBuffer.cpp
 * @brief Implementation of the IndexBuffer class for managing OpenGL index buffers.
 */

namespace graf
{
    /**
     * @brief Binds the index buffer for use in rendering.
     * 
     * Activates this index buffer in the OpenGL context by binding it to the
     * GL_ELEMENT_ARRAY_BUFFER target.
     */
    void IndexBuffer::Bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    }
    
    /**
     * @brief Creates an OpenGL index buffer with the specified data.
     * 
     * Generates an index buffer object, binds it, and uploads the provided index data
     * to the GPU with a static draw hint.
     * 
     * @param data Pointer to the index data (unsigned integers).
     * @param size Size of the data in bytes (must be a multiple of sizeof(unsigned int)).
     * @exception BufferException Thrown if data is null, size is invalid, or buffer creation fails.
     */
    void IndexBuffer::Create(const void* data, int size)
    {
        if (data == nullptr || size <= 0)
            throw BufferException("Invalid buffer data or size");

        glGenBuffers(1, &m_id);
        if (m_id == 0)
            throw BufferException("Failed to generate index buffer");

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW); ///< Upload data to GPU

        CheckGLError("Index Buffer Creation"); ///< Check for OpenGL errors

        m_IndexCount = size / 4; ///< Calculate index count assuming 4-byte unsigned ints
    }

    /**
     * @brief Gets the number of indices in the buffer.
     * @return The number of indices stored in the buffer.
     */
    int IndexBuffer::getIndexCount() const
    {
        return m_IndexCount;
    }

    /**
     * @brief Releases the index buffer’s OpenGL resources.
     * 
     * Deletes the buffer object from OpenGL memory and resets the handle if it exists.
     */
    void IndexBuffer::Release()
    {
        if (m_id != 0) 
        {
            glDeleteBuffers(1, &m_id); ///< Free GPU memory
            m_id = 0;                  ///< Reset handle to indicate deletion
        }
    }

    /**
     * @brief Unbinds the index buffer.
     * 
     * Removes this index buffer from the active OpenGL context by binding 0 to the
     * GL_ELEMENT_ARRAY_BUFFER target.
     */
    void IndexBuffer::Unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}