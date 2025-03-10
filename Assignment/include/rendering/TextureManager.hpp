#pragma once

#include <memory>
#include <unordered_map>
#include <string>

/**
 * @file TextureManager.hpp
 * @brief Defines the TextureManager class for managing OpenGL textures.
 */

namespace graf
{
    using namespace std;
    
    /**
     * @class TextureManager
     * @brief A singleton class for loading and managing OpenGL textures.
     * 
     * This class provides static methods to load textures from files and activate them
     * for rendering, using a singleton pattern to maintain a single instance with a
     * texture cache.
     */
    class TextureManager
    {
    public:
        /**
         * @brief Loads a texture from a file and adds it to the manager.
         * 
         * Loads an image file into an OpenGL texture object and stores it in the texture map.
         * 
         * @param fileName The path to the image file (e.g., "image.jpg").
         * @exception TextureException Thrown if the file doesn’t exist or loading fails.
         */
        static void sAddTextureFromFile(const string& fileName);

        /**
         * @brief Activates a texture for rendering.
         * 
         * Binds the specified texture to the OpenGL context for use in rendering.
         * 
         * @param textureName The name (file path) of the texture to activate.
         * @exception TextureException Thrown if the texture is not found in the manager.
         */
        static void sActivateTexture(const string& textureName);

        /**
         * @brief Destructor for cleaning up texture resources.
         * 
         * Releases all OpenGL texture objects stored in the manager.
         */
        ~TextureManager();

    private:
        /**
         * @brief Private constructor for singleton pattern.
         * 
         * Initializes texture parameters (wrapping, filtering) for OpenGL.
         */
        TextureManager();

        /**
         * @brief Retrieves the singleton instance of TextureManager.
         * 
         * Creates the instance on first call and returns it on subsequent calls.
         * 
         * @return A shared pointer to the TextureManager instance.
         * @exception TextureException Thrown if instance creation fails.
         */
        static shared_ptr<TextureManager> sGetInstance();

    private:
        static shared_ptr<TextureManager> ms_instance;    ///< Singleton instance of the manager.
        unordered_map<string, unsigned int> m_textureMap; ///< Map of texture names to OpenGL texture IDs.
    };
}