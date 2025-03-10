#pragma once

#include <memory>
#include <vector>
#include "vertexarrayobject.hpp"
#include "vertexbuffer.hpp"
#include "indexbuffer.hpp"
#include "vertextypes.hpp"

/**
 * @file ShapeFactory.hpp
 * @brief Defines the ShapeFactory base class for creating 3D shapes.
 */

namespace graf 
{
    /**
     * @class ShapeFactory
     * @brief Abstract base class for generating 3D shape vertex array objects (VAOs).
     * 
     * This class provides a common interface and utility functions for creating
     * various 3D shapes (e.g., cubes, pyramids) by defining their geometry and
     * texture coordinates. Derived classes implement specific shape creation logic.
     */
    class ShapeFactory {
    public:
        /**
         * @brief Creates a vertex array object for a specific 3D shape.
         * 
         * Pure virtual function to be implemented by derived classes to generate
         * the geometry of a specific shape.
         * 
         * @return A shared pointer to the created VertexArrayObject.
         * @exception BufferException Thrown if VAO creation fails in derived implementations.
         */
        virtual std::shared_ptr<VertexArrayObject> createShape() = 0;

        /**
         * @brief Virtual destructor for proper cleanup in derived classes.
         */
        virtual ~ShapeFactory() = default;

    protected:
        /**
         * @brief Constructs a VAO from vertex and index data.
         * 
         * Utility function to create a VertexArrayObject from a list of vertices
         * and indices, setting up position and texture attributes.
         * 
         * @param vertices List of vertex data defining the shape’s geometry.
         * @param indices List of indices defining the shape’s triangles.
         * @return A shared pointer to the created VertexArrayObject.
         * @exception BufferException Thrown if vertex or index data is empty or invalid.
         */
        std::shared_ptr<VertexArrayObject> createVAOFromData(const VertexList& vertices, const IndexList& indices);

        /**
         * @brief Sets texture coordinates for a single vertex.
         * 
         * Assigns the specified texture coordinates (s, t) to a vertex.
         * 
         * @param vertex The vertex to modify.
         * @param s The horizontal texture coordinate (u).
         * @param t The vertical texture coordinate (v).
         */
        void SetTextureCoords(Vertex& vertex, float s, float t);

        /**
         * @brief Assigns texture coordinates to a range of vertices.
         * 
         * Applies a set of texture coordinates to vertices starting at the specified offset.
         * 
         * @param vertices The vertex list to populate.
         * @param offset Starting index in the vertex list.
         * @param coords Vector of texture coordinate pairs (s, t) to assign.
         * @exception GrafException Thrown if coords size exceeds available vertices from offset.
         */
        void AssignTextureCoords(VertexList& vertices, int offset, const std::vector<std::pair<float, float>>& coords);

        /**
         * @brief Defines a face of the shape using vertex and texture data.
         * 
         * Creates a quadrilateral or triangular face from the specified vertex positions
         * and indices, assigning texture coordinates to each vertex.
         * 
         * @param vertices The vertex list to populate.
         * @param offset Starting index in the vertex list.
         * @param positions Array of vertex positions for the face.
         */
        void DefineFace(VertexList& vertices, int offset, const glm::vec3 positions[], 
                        const std::vector<int>& vertexIndices, 
                        const std::vector<std::pair<float, float>>& textureCoords);
        
        /**
         * @brief Generates triangle indices for the shape faces.
         * 
         * Populates the index list with triangle indices for the shape’s faces.
         * 
         * @param indices The index list to populate with triangle indices.
         * @param faceCount Number of faces to generate indices for.
         * @param offset Starting vertex index offset (default is 0).
         */
        void GenerateFaceIndices(IndexList& indices, int faceCount, int offset = 0);
    
    protected:
        static const std::vector<std::pair<float, float>> QUAD_TEXTURE_COORDS;     ///< Predefined texture coordinates for quadrilateral faces.
        static const std::vector<std::pair<float, float>> TRIANGLE_TEXTURE_COORDS; ///< Predefined texture coordinates for triangular faces.
    };
}