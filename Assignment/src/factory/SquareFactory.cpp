#include "SquareFactory.hpp"
#include <glm/glm.hpp>

/**
 * @file SquareFactory.cpp
 * @brief Implementation of the SquareFactory class for generating square shapes.
 */

namespace graf 
{
    /**
     * @brief Creates a vertex array object representing a square.
     * 
     * This function generates a 2D square with 4 vertices, duplicated to form two triangles,
     * positioned at z = -1 with a side length of 1 unit, centered at the origin.
     * Texture coordinates are assigned to map a texture across the square.
     * 
     * @return A shared pointer to the VertexArrayObject containing the square geometry.
     * @exception BufferException Thrown if vertex or index data is invalid or VAO creation fails.
     */
    std::shared_ptr<VertexArrayObject> SquareFactory::createShape() 
    {
        VertexList vertices(6); ///< 6 vertices (two triangles for a quad)
        IndexList indices = {0, 1, 2, 3, 4, 5}; ///< Indices defining two triangles: 0-1-2 and 3-4-5

        vertices[0].position = {-0.5f,  0.5f, -1.0f}; SetTextureCoords(vertices[0], 0.0f, 1.0f); ///< Top-left
        vertices[1].position = { 0.5f,  0.5f, -1.0f}; SetTextureCoords(vertices[1], 1.0f, 1.0f); ///< Top-right
        vertices[2].position = { 0.5f, -0.5f, -1.0f}; SetTextureCoords(vertices[2], 1.0f, 0.0f); ///< Bottom-right (first triangle)
        
        vertices[3].position = { 0.5f, -0.5f, -1.0f}; SetTextureCoords(vertices[3], 1.0f, 0.0f); ///< Bottom-right (second triangle)
        vertices[4].position = {-0.5f, -0.5f, -1.0f}; SetTextureCoords(vertices[4], 0.0f, 0.0f); ///< Bottom-left
        vertices[5].position = {-0.5f,  0.5f, -1.0f}; SetTextureCoords(vertices[5], 0.0f, 1.0f); ///< Top-left (repeated)

        return createVAOFromData(vertices, indices);
    }
}