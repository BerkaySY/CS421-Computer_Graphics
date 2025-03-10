#include "PyramidFactory.hpp"
#include <glm/glm.hpp>
#include <vector>

/**
 * @file PyramidFactory.cpp
 * @brief Implementation of the PyramidFactory class for generating pyramid shapes.
 */

namespace graf 
{
    /**
     * @brief Creates a vertex array object representing a pyramid.
     * 
     * This function generates a 3D pyramid with 5 faces: 4 triangular side faces
     * and 1 square base. The apex is at (0, 0.5, 0), and the base is a 1x1 square
     * at y = -0.5, centered at the origin.
     * 
     * @return A shared pointer to the VertexArrayObject containing the pyramid geometry.
     * @exception BufferException Thrown if vertex or index data is invalid or VAO creation fails.
     */
    std::shared_ptr<VertexArrayObject> PyramidFactory::createShape() 
    {
        glm::vec3 positions[] = {
            { 0.0f,  0.5f,  0.0f}, // Apex (top)
            {-0.5f, -0.5f,  0.5f}, // Front-left base
            { 0.5f, -0.5f,  0.5f}, // Front-right base
            { 0.5f, -0.5f, -0.5f}, // Back-right base
            {-0.5f, -0.5f, -0.5f}  // Back-left base
        };

        VertexList vertices(16);
        IndexList indices = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 12, 14, 15};

        // Define each face with texture coordinates
        DefineFace(vertices, 0,  positions, {0, 1, 2}, TRIANGLE_TEXTURE_COORDS); // Front
        DefineFace(vertices, 3,  positions, {0, 2, 3}, TRIANGLE_TEXTURE_COORDS); // Right
        DefineFace(vertices, 6,  positions, {0, 3, 4}, TRIANGLE_TEXTURE_COORDS); // Back
        DefineFace(vertices, 9,  positions, {0, 4, 1}, TRIANGLE_TEXTURE_COORDS); // Left
        DefineFace(vertices, 12, positions, {1, 2, 3, 4}, QUAD_TEXTURE_COORDS);  // Base

        return createVAOFromData(vertices, indices);
    }
}