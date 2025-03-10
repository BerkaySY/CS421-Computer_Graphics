#pragma once 

#include "ShapeFactory.hpp"

/**
 * @file SquareFactory.hpp
 * @brief Defines the SquareFactory class for creating square shapes.
 */

namespace graf 
{
    /**
     * @class SquareFactory
     * @brief A factory class for generating square shapes as vertex array objects.
     * 
     * This class inherits from ShapeFactory and creates a 2D square with 4 vertices,
     * positioned in the XY plane at z = -1, centered at the origin with a side length of 1 unit.
     */
    class SquareFactory : public ShapeFactory 
    {
    public:
        /**
         * @brief Creates a vertex array object representing a square.
         * @return A shared pointer to the VertexArrayObject containing the square geometry.
         * @exception BufferException Thrown if VAO creation fails due to invalid data.
         */
        std::shared_ptr<VertexArrayObject> createShape() override;
    };
}