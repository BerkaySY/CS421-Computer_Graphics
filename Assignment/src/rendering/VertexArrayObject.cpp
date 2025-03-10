#include <glad/glad.h>
#include "VertexArrayObject.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Exceptions.hpp"
#include "ErrorCheck.hpp"

/**
 * @file VertexArrayObject.cpp
 * @brief Implementation of the VertexArrayObject class for managing OpenGL VAOs.
 */

namespace graf
{
    /**
     * @brief Creates a new OpenGL vertex array object.
     * 
     * Generates a VAO handle and initializes its stride to zero.
     * 
     * @exception BufferException Thrown if VAO generation fails due to OpenGL error.
     */
    void VertexArrayObject::Create()
    {
        glGenVertexArrays(1, &m_id); ///< Generate VAO ID
        if (m_id == 0)
            throw BufferException("Failed to generate Vertex Array Object"); ///< Check generation success
            
        CheckGLError("VAO generation"); ///< Verify no OpenGL errors
        m_stride = 0; ///< Initialize stride
    }

    /**
     * @brief Binds the VAO for rendering.
     * 
     * Activates this VAO in the OpenGL context.
     */
    void VertexArrayObject::Bind()
    {
        glBindVertexArray(m_id);
    }

    /**
     * @brief Sets the vertex buffer for the VAO.
     * 
     * Associates the provided vertex buffer with the VAO and binds it.
     * 
     * @param p_vb Shared pointer to the VertexBuffer to set.
     * @exception BufferException Thrown if the vertex buffer is null or binding fails.
     */
    void VertexArrayObject::SetVertexBuffer(std::shared_ptr<VertexBuffer> p_vb)
    {
        if (!p_vb) 
            throw BufferException("Null vertex buffer"); ///< Validate input

        mp_vb = p_vb; ///< Store vertex buffer pointer
        try 
        {
            Bind(); ///< Bind VAO
            mp_vb->Bind(); ///< Bind vertex buffer
            CheckGLError("Vertex buffer binding"); ///< Check for errors
        } 
        catch (const GrafException& e) 
        {
            Unbind(); ///< Cleanup on failure
            throw BufferException("Failed to set vertex buffer: " + std::string(e.what())); ///< Rethrow with context
        }
    }

    /**
     * @brief Draws the geometry represented by the VAO.
     * 
     * Renders triangles using the bound index buffer and vertex attributes.
     * 
     * @exception BufferException Thrown if no index buffer is bound or drawing fails.
     */
    void VertexArrayObject::Draw()
    {
        if (!mp_ib) 
            throw BufferException("No index buffer bound for drawing"); ///< Validate index buffer
        
        glDrawElements(GL_TRIANGLES, mp_ib->getIndexCount(), GL_UNSIGNED_INT, 0); ///< Draw triangles
        CheckGLError("Draw call"); ///< Check for OpenGL errors
    }

    /**
     * @brief Sets the index buffer for the VAO.
     * 
     * Associates the provided index buffer with the VAO and binds it.
     * 
     * @param p_ib Shared pointer to the IndexBuffer to set.
     * @exception BufferException Thrown if the index buffer is null or binding fails.
     */
    void VertexArrayObject::SetIndexBuffer(std::shared_ptr<IndexBuffer> p_ib)
    {
        if (!p_ib) 
            throw BufferException("Null index buffer"); ///< Validate input
        
        mp_ib = p_ib; ///< Store index buffer pointer
        try
        {
            Bind(); ///< Bind VAO
            mp_ib->Bind(); ///< Bind index buffer          
            CheckGLError("Index buffer binding"); ///< Check for errors
        }
        catch (const GrafException& e) 
        {
            Unbind(); ///< Cleanup on failure
            throw BufferException("Failed to set index buffer: " + std::string(e.what())); ///< Rethrow with context
        }
    }

    /**
     * @brief Adds a vertex attribute to the VAO’s layout.
     * 
     * Appends the attribute type to the list and updates the stride.
     * 
     * @param type The type of attribute to add (e.g., Position, Texture).
     */
    void VertexArrayObject::AddVertexAttribute(VertexAttributeType type)
    {
        m_attributes.push_back(type); ///< Add attribute to list
        m_stride += getTypeSize(type); ///< Increment stride by attribute size
    }

    /**
     * @brief Activates the vertex attributes for rendering.
     * 
     * Configures OpenGL attribute pointers based on the attribute list and stride.
     * 
     * @exception BufferException Thrown if no attributes are specified or setup fails.
     */
    void VertexArrayObject::ActivateAttributes()
    {
        if (m_attributes.empty()) 
            throw BufferException("No vertex attributes specified"); ///< Validate attributes exist
        
        int location = 0; ///< Starting offset for attributes
        for (int i = 0; i < m_attributes.size(); i++)
        {
            int attributeSize = getTypeSize(m_attributes[i]); ///< Size of current attribute
            int elementCount = attributeSize / sizeof(float); ///< Number of float components
        
            glVertexAttribPointer(i, 
                                  elementCount, 
                                  GL_FLOAT, 
                                  GL_FALSE, 
                                  m_stride, 
                                  (void*)location); ///< Set attribute pointer
            CheckGLError("Vertex attribute setup"); ///< Check for errors

            glEnableVertexAttribArray(i); ///< Enable attribute
            CheckGLError("Vertex attribute enable"); ///< Check for errors

            location += attributeSize; ///< Update offset for next attribute
        }
    }

    /**
     * @brief Gets the size in bytes of a vertex attribute type.
     * 
     * Determines the byte size based on the attribute type.
     * 
     * @param type The attribute type (e.g., Position, Texture).
     * @return The size in bytes: 12 for Position/Normal, 16 for Color, 8 for Texture, 0 for unknown.
     */
    int VertexArrayObject::getTypeSize(VertexAttributeType type)
    {
        int size = 0;

        switch (type)
        {
            case VertexAttributeType::Position: ///< 3 floats (x, y, z)
            case VertexAttributeType::Normal:   ///< 3 floats (nx, ny, nz)
                size = sizeof(float) * 3;
                break;
            case VertexAttributeType::Color:    ///< 4 floats (r, g, b, a)
                size = sizeof(float) * 4;
                break;
            case VertexAttributeType::Texture:  ///< 2 floats (s, t)
                size = sizeof(float) * 2;
                break;
            default:
                break; ///< Unknown type returns 0
        }
        return size;
    }
   
    /**
     * @brief Releases the VAO’s OpenGL resources.
     * 
     * Deletes the VAO and releases the associated vertex buffer.
     */
    void VertexArrayObject::Release()
    {
        glDeleteVertexArrays(1, &m_id); ///< Free VAO
        mp_vb->Release(); ///< Release vertex buffer
    }

    /**
     * @brief Unbinds the VAO.
     * 
     * Unbinds the VAO and its associated vertex and index buffers from the OpenGL context.
     */
    void VertexArrayObject::Unbind()
    {
        glBindVertexArray(0); ///< Unbind VAO
        mp_ib->Unbind(); ///< Unbind index buffer
        mp_vb->Unbind(); ///< Unbind vertex buffer
    }
}