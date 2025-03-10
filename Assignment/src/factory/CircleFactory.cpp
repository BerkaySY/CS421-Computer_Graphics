#include "CircleFactory.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

/**
 * @file CircleFactory.cpp
 * @brief Implementation of the CircleFactory class for generating circular shapes.
 */

namespace graf 
{
    /**
     * @brief Constructs a CircleFactory with a specified angular resolution.
     * @param anglesInDegrees The angle step (in degrees) between consecutive vertices.
     *        Must be a positive value that divides 360 evenly for a closed shape.
     */
    CircleFactory::CircleFactory(int anglesInDegrees) : m_angles(anglesInDegrees) {}

    /**
     * @brief Creates a vertex array object representing a circle.
     * 
     * This function generates a circle as a triangle fan, with the center at (0,0,0)
     * and a radius of 1 unit. The number of vertices is determined by dividing 360
     * degrees by the angle step specified in the constructor.
     * 
     * @return A shared pointer to the VertexArrayObject containing the circle geometry.
     * @exception BufferException Thrown if vertex or index data is invalid or VAO creation fails.
     */
    std::shared_ptr<VertexArrayObject> CircleFactory::createShape() 
    {
        int vertexCount = 360 / m_angles; ///< Number of vertices in the circle.
        int faceCount = vertexCount - 2;  ///< Number of triangular faces (excluding center and edge).

        VertexList vertices(vertexCount);
        IndexList indices;
        std::vector<std::pair<float, float>> textureCoords(vertexCount);

        // Generate vertex positions and texture coordinates
        for (int i = 0; i < vertexCount; i++) 
        {
            double currentAngle = m_angles * i;
            vertices[i].position.x = glm::cos(glm::radians(currentAngle));
            vertices[i].position.y = glm::sin(glm::radians(currentAngle));
            vertices[i].position.z = 0.0f;
            textureCoords[i] = {0.5f + 0.5f * glm::cos(glm::radians(currentAngle)),
                                0.5f + 0.5f * glm::sin(glm::radians(currentAngle))};
        }

        AssignTextureCoords(vertices, 0, textureCoords);

        // Generate triangle indices as a fan from the center
        for (int i = 0; i < faceCount; i++) 
        {
            indices.push_back(0);         // Center vertex
            indices.push_back(i + 2);     // Next vertex
            indices.push_back(i + 1);     // Current vertex
        }

        return createVAOFromData(vertices, indices);
    }
}