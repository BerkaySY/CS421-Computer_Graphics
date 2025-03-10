#pragma once

#include "ShapeFactory.hpp"
#include <vector>

/**
 * @file CubeFactory.hpp
 * @brief Defines the CubeFactory class for creating cube shapes.
 */

namespace graf 
{
    /**
     * @class CubeFactory
     * @brief A factory class for generating cube shapes as vertex array objects.
     * 
     * This class inherits from ShapeFactory and creates a 3D cube with 6 faces,
     * each defined as a quadrilateral. The cube is centered at the origin with
     * a side length of 1 unit.
     */
    class CubeFactory : public ShapeFactory 
    {
    public:
        /**
         * @brief Creates a vertex array object representing a cube.
         * @return A shared pointer to the VertexArrayObject containing the cube geometry.
         * @exception BufferException Thrown if VAO creation fails due to invalid data.
         */
        std::shared_ptr<VertexArrayObject> createShape() override;
    };
}