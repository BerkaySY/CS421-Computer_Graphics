#pragma once

#include "SquareFactory.hpp"
#include "CircleFactory.hpp"
#include "CubeFactory.hpp"
#include "PyramidFactory.hpp"
#include "FrustumFactory.hpp"
#include "Exceptions.hpp"
#include <map>

/**
 * @file ShapeFactoryManager.hpp
 * @brief Defines the ShapeFactoryManager class for managing shape factories.
 */

namespace graf
{
    /**
     * @enum ShapeTypes
     * @brief Enumerates the supported 3D shape types.
     * 
     * Defines the types of shapes that can be created by the ShapeFactoryManager.
     */
    enum class ShapeTypes
    {
        Circle,   ///< A 2D circle approximated by a polygon.
        Square,   ///< A 2D square.
        Cube,     ///< A 3D cube with 6 faces.
        Pyramid,  ///< A 3D pyramid with 4 side faces and a square base.
        Frustum,  ///< A 3D frustum with a smaller top and larger base.
    };

    /**
     * @class ShapeFactoryManager
     * @brief A manager class for creating and caching 3D shapes.
     * 
     * This class maintains a collection of shape factories and a cache of created
     * vertex array objects (VAOs) to efficiently generate and reuse 3D shapes.
     */
    class ShapeFactoryManager 
    {
    public:
        /**
         * @brief Constructs a ShapeFactoryManager instance.
         * 
         * Initializes the factory map with instances of supported shape factories.
         */
        ShapeFactoryManager();

        /**
         * @brief Creates or retrieves a vertex array object for a specified shape type.
         * 
         * Returns a cached VAO if available; otherwise, creates a new one using the
         * appropriate factory and caches it.
         * 
         * @param shapeType The type of shape to create (e.g., ShapeTypes::Cube).
         * @return A shared pointer to the VertexArrayObject for the requested shape.
         * @exception GrafException Thrown if an unknown shape type is requested.
         */
        std::shared_ptr<graf::VertexArrayObject> createShape(graf::ShapeTypes shapeType);

    private:
        std::map<graf::ShapeTypes, std::unique_ptr<graf::ShapeFactory>> factories; ///< Map of shape types to their factories.
        std::map<graf::ShapeTypes, std::shared_ptr<graf::VertexArrayObject>> shapeCache; ///< Cache of created VAOs by shape type.
    };
}