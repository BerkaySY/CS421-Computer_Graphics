#include "FrustumFactory.hpp"
#include <glm/glm.hpp>
#include <vector>

/**
 * @file FrustumFactory.cpp
 * @brief Implementation of the FrustumFactory class for generating frustum shapes.
 */

namespace graf 
{
    /**
     * @brief Creates a vertex array object representing a frustum.
     * 
     * This function generates a 3D frustum with 6 quadrilateral faces, each split into
     * two triangles. The frustum has a smaller square top (side length 1) at y = 0.5
     * and a larger square base (side length 2) at y = -0.5, centered at the origin.
     * 
     * @return A shared pointer to the VertexArrayObject containing the frustum geometry.
     * @exception BufferException Thrown if vertex or index data is invalid or VAO creation fails.
     */
    std::shared_ptr<VertexArrayObject> FrustumFactory::createShape() 
    {
        glm::vec3 positions[] = {
            {-0.5f,  0.5f,  0.5f}, { 0.5f,  0.5f,  0.5f}, { 1.0f, -0.5f,  1.0f}, {-1.0f, -0.5f,  1.0f}, // Front
            {-0.5f,  0.5f, -0.5f}, { 0.5f,  0.5f, -0.5f}, { 1.0f, -0.5f, -1.0f}, {-1.0f, -0.5f, -1.0f}  // Back
        };

        VertexList vertices(24);
        IndexList indices;

        // Define each face with texture coordinates
        DefineFace(vertices, 0,  positions, {0, 1, 2, 3}, QUAD_TEXTURE_COORDS); // Front
        DefineFace(vertices, 4,  positions, {1, 5, 6, 2}, QUAD_TEXTURE_COORDS); // Right
        DefineFace(vertices, 8,  positions, {5, 4, 7, 6}, QUAD_TEXTURE_COORDS); // Back
        DefineFace(vertices, 12, positions, {4, 0, 3, 7}, QUAD_TEXTURE_COORDS); // Left
        DefineFace(vertices, 16, positions, {3, 2, 6, 7}, QUAD_TEXTURE_COORDS); // Bottom
        DefineFace(vertices, 20, positions, {0, 1, 5, 4}, QUAD_TEXTURE_COORDS); // Top

        GenerateFaceIndices(indices, 6);
        return createVAOFromData(vertices, indices);
    }
}