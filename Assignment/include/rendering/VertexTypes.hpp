#pragma once

#include <glm/glm.hpp>
#include <vector>

/**
 * @file VertexTypes.hpp
 * @brief Defines vertex-related data structures.
 */

namespace graf
{
    /**
     * @class Vertex
     * @brief Represents a single vertex with position and texture coordinates.
     * 
     * This class encapsulates the basic attributes of a vertex used in 3D rendering,
     * including its position in 3D space and texture coordinates for mapping.
     */
    class Vertex
    {
    public:
        glm::vec3 position; ///< 3D position of the vertex (x, y, z).
        glm::vec2 texture;  ///< 2D texture coordinates (s, t).
    };

    /**
     * @brief Alias for a list of vertices.
     * 
     * Represents a collection of Vertex objects, typically used to define the geometry
     * of a 3D shape.
     */
    using VertexList = std::vector<Vertex>;

    /**
     * @brief Alias for a list of indices.
     * 
     * Represents a collection of unsigned integers that define the order in which
     * vertices are connected to form triangles in a 3D shape.
     */
    using IndexList = std::vector<unsigned int>;
}