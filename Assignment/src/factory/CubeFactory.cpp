#include "CubeFactory.hpp"
#include <glm/glm.hpp>
#include <vector>

/**
 * @file CubeFactory.cpp
 * @brief Implementation of the CubeFactory class for generating cube shapes.
 */

namespace graf 
{
    /**
     * @brief Creates a vertex array object representing a cube.
     * 
     * This function generates a 3D cube with 6 quadrilateral faces, each split into
     * two triangles. The cube is centered at the origin with a side length of 1 unit.
     * Vertex positions and texture coordinates are defined for each face.
     * 
     * @return A shared pointer to the VertexArrayObject containing the cube geometry.
     * @exception BufferException Thrown if vertex or index data is invalid or VAO creation fails.
     */
    std::shared_ptr<VertexArrayObject> CubeFactory::createShape() 
    {
        glm::vec3 positions[] = {
            {-0.5f,  0.5f, 0.5f}, { 0.5f,  0.5f, 0.5f}, { 0.5f, -0.5f, 0.5f}, {-0.5f, -0.5f, 0.5f}, // Front face
            {-0.5f,  0.5f,-0.5f}, { 0.5f,  0.5f,-0.5f}, { 0.5f, -0.5f,-0.5f}, {-0.5f, -0.5f,-0.5f}  // Back face
        };

        VertexList vertices(24);
        IndexList indices;

        // Define each face with texture coordinates
        DefineFace(vertices, 0,  positions, {0, 1, 2, 3}, QUAD_TEXTURE_COORDS); // Front
        DefineFace(vertices, 4,  positions, {1, 5, 6, 2}, QUAD_TEXTURE_COORDS); // Right
        DefineFace(vertices, 8,  positions, {4, 5, 1, 0}, QUAD_TEXTURE_COORDS); // Top
        DefineFace(vertices, 12, positions, {4, 0, 3, 7}, QUAD_TEXTURE_COORDS); // Left
        DefineFace(vertices, 16, positions, {5, 4, 7, 6}, QUAD_TEXTURE_COORDS); // Back
        DefineFace(vertices, 20, positions, {3, 2, 6, 7}, QUAD_TEXTURE_COORDS); // Bottom

        GenerateFaceIndices(indices, 6);
        return createVAOFromData(vertices, indices);
    }
}