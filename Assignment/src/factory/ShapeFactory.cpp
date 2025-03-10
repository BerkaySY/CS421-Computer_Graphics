#include "ShapeFactory.hpp"
#include "Exceptions.hpp"
#include <string>

/**
 * @file ShapeFactory.cpp
 * @brief Implementation of the ShapeFactory base class for creating 3D shapes.
 */

namespace graf 
{
    const std::vector<std::pair<float, float>> ShapeFactory::QUAD_TEXTURE_COORDS = {{0.0f, 1.0f}, 
                                                                                    {1.0f, 1.0f}, 
                                                                                    {1.0f, 0.0f}, 
                                                                                    {0.0f, 0.0f}}; ///< Texture coords for quads: top-left, top-right, bottom-right, bottom-left
                                                                                    
    const std::vector<std::pair<float, float>> ShapeFactory::TRIANGLE_TEXTURE_COORDS = {{0.5f, 1.0f}, 
                                                                                        {0.0f, 0.0f}, 
                                                                                        {1.0f, 0.0f}}; ///< Texture coords for triangles: top-center, bottom-left, bottom-right

    /**
     * @brief Constructs a VAO from vertex and index data.
     * 
     * Creates and configures a VertexArrayObject with associated vertex and index buffers,
     * setting up position and texture attributes for rendering.
     * 
     * @param vertices List of vertex data defining the shape’s geometry.
     * @param indices List of indices defining the shape’s triangles.
     * @return A shared pointer to the created VertexArrayObject.
     * @exception BufferException Thrown if vertex or index data is empty, buffers are null, or VAO setup fails.
     */
    std::shared_ptr<VertexArrayObject> ShapeFactory::createVAOFromData(const VertexList& vertices, const IndexList& indices) {
        auto p_va = std::make_shared<VertexArrayObject>(); ///< VAO smart pointer
        auto p_vb = std::make_shared<VertexBuffer>();      ///< Vertex buffer smart pointer
        auto p_ib = std::make_shared<IndexBuffer>();       ///< Index buffer smart pointer

        if (vertices.empty() || indices.empty())
            throw BufferException("Empty vertex or index data in createVAOFromData");

        p_vb->Create(vertices.data(), sizeof(Vertex) * vertices.size()); ///< Upload vertex data
        p_ib->Create(indices.data(), sizeof(unsigned int) * indices.size()); ///< Upload index data

        if (!p_va || !p_vb || !p_ib)
            throw BufferException("Null buffer in createVAOFromData");

        try 
        {
            p_va->Create();                                ///< Initialize VAO
            p_va->SetVertexBuffer(p_vb);                   ///< Associate vertex buffer
            p_va->SetIndexBuffer(p_ib);                    ///< Associate index buffer
            p_va->AddVertexAttribute(VertexAttributeType::Position); ///< Add position attribute
            p_va->AddVertexAttribute(VertexAttributeType::Texture);  ///< Add texture attribute
            p_va->ActivateAttributes();                    ///< Enable attributes
            p_va->Unbind();                                ///< Unbind VAO
            return p_va;
        } 
        catch (const std::exception& e) 
        {
            throw BufferException("VAO setup failed: " + std::string(e.what())); ///< Rethrow with context
        }
    }

    /**
     * @brief Sets texture coordinates for a single vertex.
     * 
     * Assigns the specified (s, t) coordinates to the vertex’s texture attribute.
     * 
     * @param vertex The vertex to modify.
     * @param s The horizontal texture coordinate (u).
     * @param t The vertical texture coordinate (v).
     */
    void ShapeFactory::SetTextureCoords(Vertex& vertex, float s, float t) {
        vertex.texture.s = s; ///< Set horizontal coordinate
        vertex.texture.t = t; ///< Set vertical coordinate
    }

    /**
     * @brief Assigns texture coordinates to a range of vertices.
     * 
     * Applies the provided texture coordinates to vertices starting at the specified offset.
     * 
     * @param vertices The vertex list to populate.
     * @param offset Starting index in the vertex list.
     * @param coords Vector of texture coordinate pairs (s, t) to assign.
     * @exception GrafException Thrown if coords size exceeds available vertices from offset.
     */
    void ShapeFactory::AssignTextureCoords(VertexList& vertices, int offset, const std::vector<std::pair<float, float>>& coords) 
    {
        if (offset + coords.size() > vertices.size())
            throw GrafException("Texture coords size exceeds vertex list size");

        for (size_t i = 0; i < coords.size(); i++)
            SetTextureCoords(vertices[offset + i], coords[i].first, coords[i].second); ///< Assign coords iteratively
    }

    /**
     * @brief Defines a face of the shape using vertex and texture data.
     * 
     * Creates a quadrilateral or triangular face from the specified vertex positions
     * and indices, assigning texture coordinates to each vertex.
     * 
     * @param vertices The vertex list to populate.
     * @param offset Starting index in the vertex list.
     * @param positions Array of vertex positions for the face.
     * @param vertexIndices List of vertex indices for the face.
     * @param textureCoords List of texture coordinates for the face.
     */
    void ShapeFactory::DefineFace(VertexList &vertices, int offset, const glm::vec3 positions[], 
                                  const std::vector<int> &vertexIndices, 
                                  const std::vector<std::pair<float, float>> &textureCoords)
    {
        if (offset + vertexIndices.size() > vertices.size())
            throw GrafException("Vertex indices exceed vertex list size");

        for (size_t i = 0; i < vertexIndices.size(); i++) 
            vertices[offset + i].position = positions[vertexIndices[i]];

        AssignTextureCoords(vertices, offset, textureCoords);
    }

    /**
     * @brief Generates triangle indices for the shape faces.
     * 
     * Populates the index list with triangle indices for the shape’s faces.
     * 
     * @param indices The index list to populate with triangle indices.
     * @param faceCount Number of faces to generate indices for.
     * @param offset Starting vertex index offset (default is 0).
     */
    void ShapeFactory::GenerateFaceIndices(IndexList &indices, int faceCount, int offset)
    {
        for (int i = 0; i < faceCount; i++) 
        {
            indices.push_back(offset + i * 4);     // First triangle: 0-2-1
            indices.push_back(offset + i * 4 + 2);
            indices.push_back(offset + i * 4 + 1);
            
            indices.push_back(offset + i * 4);     // Second triangle: 0-3-2
            indices.push_back(offset + i * 4 + 3);
            indices.push_back(offset + i * 4 + 2);
        }
    }
}