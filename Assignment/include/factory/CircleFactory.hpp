#pragma once

#include "ShapeFactory.hpp"
#include <vector>

/**
 * @file CircleFactory.hpp
 * @brief Defines the CircleFactory class for creating circular shapes.
 */

namespace graf 
{
    /**
     * @class CircleFactory
     * @brief A factory class for generating circular shapes as vertex array objects.
     * 
     * This class inherits from ShapeFactory and creates a 2D circle approximated by
     * a polygon with a specified number of segments (angles). The circle is centered
     * at the origin with a radius of 1 unit.
     */
    class CircleFactory : public ShapeFactory 
    {
    public:
        /**
         * @brief Constructs a CircleFactory with a specified angular resolution.
         * @param anglesInDegrees The angle step (in degrees) between consecutive vertices.
         *        Smaller values result in a smoother circle but increase vertex count.
         */
        explicit CircleFactory(int anglesInDegrees);

        /**
         * @brief Creates a vertex array object representing a circle.
         * @return A shared pointer to the VertexArrayObject containing the circle geometry.
         * @exception BufferException Thrown if VAO creation fails due to invalid data.
         */
        std::shared_ptr<VertexArrayObject> createShape() override;

    private:
        int m_angles; ///< The angle step (in degrees) used to approximate the circle.
    };
}