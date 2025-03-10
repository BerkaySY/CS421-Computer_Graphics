#pragma once

#include <memory>
#include <vector>

/**
 * @file VertexArrayObject.hpp
 * @brief Defines the VertexArrayObject class for managing OpenGL VAOs.
 */

namespace graf
{
    using namespace std;

    /**
     * @enum VertexAttributeType
     * @brief Enumerates supported vertex attribute types.
     * 
     * Defines the types of attributes that can be associated with a vertex in a VAO.
     */
    enum class VertexAttributeType
    {
        Position, ///< 3D position of the vertex (x, y, z).
        Color,    ///< RGBA color of the vertex.
        Normal,   ///< 3D normal vector for lighting.
        Texture   ///< 2D texture coordinates (s, t).
    };

    /**
     * @brief Alias for a list of vertex attribute types.
     * 
     * Represents a collection of VertexAttributeType values defining the layout of vertex data.
     */
    using AttributeList = vector<VertexAttributeType>;

    class VertexBuffer;
    class IndexBuffer;

    /**
     * @class VertexArrayObject
     * @brief A class for handling OpenGL vertex array objects (VAOs).
     * 
     * This class encapsulates the creation, configuration, and rendering of a VAO,
     * which combines vertex buffers, index buffers, and attribute layouts for efficient
     * 3D rendering.
     */
    class VertexArrayObject
    {
    public:
        /**
         * @brief Creates a new OpenGL vertex array object.
         * 
         * Generates a VAO handle and initializes its state.
         * @exception BufferException Thrown if VAO generation fails.
         */
        void Create();

        /**
         * @brief Sets the vertex buffer for the VAO.
         * @param p_vb Shared pointer to the VertexBuffer containing vertex data.
         * @exception BufferException Thrown if the vertex buffer is null or binding fails.
         */
        void SetVertexBuffer(shared_ptr<VertexBuffer> p_vb);

        /**
         * @brief Sets the index buffer for the VAO.
         * @param p_ib Shared pointer to the IndexBuffer containing index data.
         * @exception BufferException Thrown if the index buffer is null or binding fails.
         */
        void SetIndexBuffer(shared_ptr<IndexBuffer> p_ib);

        /**
         * @brief Adds a vertex attribute to the VAO’s layout.
         * @param type The type of attribute to add (e.g., Position, Texture).
         */
        void AddVertexAttribute(VertexAttributeType type);

        /**
         * @brief Activates the vertex attributes for rendering.
         * 
         * Configures the attribute pointers based on the added attributes and stride.
         * @exception BufferException Thrown if no attributes are specified or setup fails.
         */
        void ActivateAttributes();

        /**
         * @brief Binds the VAO for rendering.
         * 
         * Makes this VAO the active one in the OpenGL context.
         */
        void Bind();

        /**
         * @brief Unbinds the VAO.
         * 
         * Removes this VAO from the active OpenGL context and unbinds associated buffers.
         */
        void Unbind();

        /**
         * @brief Releases the VAO’s OpenGL resources.
         * 
         * Deletes the VAO and releases the vertex buffer resources.
         */
        void Release();

        /**
         * @brief Draws the geometry represented by the VAO.
         * 
         * Renders the object using the bound index buffer and vertex attributes.
         * @exception BufferException Thrown if no index buffer is bound.
         */
        void Draw();

    private:
        /**
         * @brief Gets the size in bytes of a vertex attribute type.
         * @param type The attribute type (e.g., Position, Texture).
         * @return The size in bytes of the attribute.
         */
        int getTypeSize(VertexAttributeType type);

    private:
        unsigned int    m_id;           ///< OpenGL handle for the VAO.
        shared_ptr<VertexBuffer> mp_vb; ///< Pointer to the associated vertex buffer.
        shared_ptr<IndexBuffer> mp_ib;  ///< Pointer to the associated index buffer.
        unsigned int    m_stride;       ///< Total size in bytes of one vertex’s attributes.
        AttributeList   m_attributes;   ///< List of attribute types in the vertex layout.
    };
}