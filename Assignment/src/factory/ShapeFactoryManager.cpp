#include "ShapeFactoryManager.hpp"

/**
 * @file ShapeFactoryManager.cpp
 * @brief Implementation of the ShapeFactoryManager class for managing shape factories.
 */

namespace graf
{
    /**
     * @brief Constructs a ShapeFactoryManager instance.
     * 
     * Initializes the factories map with instances of supported shape factories.
     * Each factory is responsible for creating a specific type of 3D shape.
     */
    ShapeFactoryManager::ShapeFactoryManager()
    {
        factories[graf::ShapeTypes::Square]  = std::make_unique<graf::SquareFactory>();   ///< Factory for square shapes
        factories[graf::ShapeTypes::Circle]  = std::make_unique<graf::CircleFactory>(10); ///< Factory for circles with 10-degree segments
        factories[graf::ShapeTypes::Cube]    = std::make_unique<graf::CubeFactory>();       ///< Factory for cube shapes
        factories[graf::ShapeTypes::Pyramid] = std::make_unique<graf::PyramidFactory>(); ///< Factory for pyramid shapes
        factories[graf::ShapeTypes::Frustum] = std::make_unique<graf::FrustumFactory>(); ///< Factory for frustum shapes
    }

    /**
     * @brief Creates or retrieves a vertex array object for a specified shape type.
     * 
     * Checks the cache first; if the shape is not cached, creates it using the
     * corresponding factory and stores it in the cache before returning.
     * 
     * @param shapeType The type of shape to create (e.g., ShapeTypes::Cube).
     * @return A shared pointer to the VertexArrayObject for the requested shape.
     * @exception GrafException Thrown if the specified shape type is not supported.
     */
    std::shared_ptr<graf::VertexArrayObject> ShapeFactoryManager::createShape(graf::ShapeTypes shapeType)
    {
        if (shapeCache.count(shapeType) > 0)
            return shapeCache[shapeType]; ///< Return cached VAO if available

        auto it = factories.find(shapeType);
        if (it == factories.end())
            throw graf::GrafException("Unknown shape type"); ///< Throw if factory not found
        
        auto shape = it->second->createShape(); ///< Create new shape using factory
        shapeCache[shapeType] = shape;          ///< Cache the created shape
        return shape;
    }
}