#pragma once

#include "ShapeFactory.hpp"
#include <vector>

/**
 * @file PyramidFactory.hpp
 * @brief Defines the PyramidFactory class for creating pyramid shapes.
 */

namespace graf 
{
    /**
     * @class PyramidFactory
     * @brief A factory class for generating pyramid shapes as vertex array objects.
     * 
     * This class inherits from ShapeFactory and creates a 3D pyramid (tetrahedron-like)
     * with 5 faces: 4 triangular side faces and 1 square base. The pyramid is centered
     * at the origin with the apex at y = 0.5 and the base at y = -0.5.
     */
    class PyramidFactory : public ShapeFactory 
    {
    public:
        /**
         * @brief Creates a vertex array object representing a pyramid.
         * @return A shared pointer to the VertexArrayObject containing the pyramid geometry.
         * @exception BufferException Thrown if VAO creation fails due to invalid data.
         */
        std::shared_ptr<VertexArrayObject> createShape() override;
    };
}