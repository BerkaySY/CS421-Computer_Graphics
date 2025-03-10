#pragma once

#include "ShapeFactory.hpp"
#include <vector>

/**
 * @file FrustumFactory.hpp
 * @brief Defines the FrustumFactory class for creating frustum shapes.
 */

namespace graf 
{
    /**
     * @class FrustumFactory
     * @brief A factory class for generating frustum shapes as vertex array objects.
     * 
     * This class inherits from ShapeFactory and creates a 3D frustum (truncated pyramid)
     * with 6 faces, each defined as a quadrilateral. The frustum has a smaller square top
     * and a larger square base, centered at the origin.
     */
    class FrustumFactory : public ShapeFactory 
    {
    public:
        /**
         * @brief Creates a vertex array object representing a frustum.
         * @return A shared pointer to the VertexArrayObject containing the frustum geometry.
         * @exception BufferException Thrown if VAO creation fails due to invalid data.
         */
        std::shared_ptr<VertexArrayObject> createShape() override;
    };
}