#define STB_IMAGE_IMPLEMENTATION
#include "TextureManager.hpp"
#include "Exceptions.hpp"
#include "Errorcheck.hpp"
#include <glad/glad.h>
#include <stb/stb_image.h>
#include <filesystem>

/**
 * @file TextureManager.cpp
 * @brief Implementation of the TextureManager class for managing OpenGL textures.
 */

namespace graf
{
    std::shared_ptr<TextureManager> TextureManager::ms_instance = nullptr; ///< Singleton instance initialized to null

    /**
     * @brief Activates a texture for rendering.
     * 
     * Binds the texture associated with the given name to the OpenGL context for use in rendering.
     * 
     * @param textureName The name (file path) of the texture to activate.
     * @exception TextureException Thrown if the texture is not found in the manager.
     */
    void TextureManager::sActivateTexture(const string& textureName)
    {
        auto manager = sGetInstance(); ///< Get singleton instance

        auto it = manager->m_textureMap.find(textureName);
        
        if (it == manager->m_textureMap.end()) 
            throw TextureException("Texture not found: " + textureName); ///< Throw if texture not loaded
        
        glBindTexture(GL_TEXTURE_2D, it->second); ///< Bind texture to GL_TEXTURE_2D target
        CheckGLError("Texture activation");       ///< Check for OpenGL errors
    }

    /**
     * @brief Loads a texture from a file and adds it to the manager.
     * 
     * Loads an image file using stb_image, creates an OpenGL texture object, and stores it
     * in the texture map. Skips loading if the texture is already present.
     * 
     * @param fileName The path to the image file (e.g., "image.jpg").
     * @exception TextureException Thrown if the file doesn’t exist or loading fails.
     */
    void TextureManager::sAddTextureFromFile(const string& fileName)
    {
        if (!std::filesystem::exists(fileName)) 
            throw TextureException("Texture file does not exist: " + fileName); ///< Check file existence
        
        auto manager = sGetInstance();
        if (manager->m_textureMap.find(fileName) != manager->m_textureMap.end()) 
            return; ///< Skip if texture already loaded
        
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true); ///< Flip image vertically during load
        unsigned char *data = stbi_load(fileName.data(), &width, &height, &nrChannels, 0); 
        
        if (!data) 
        {
            throw TextureException("Failed to load texture: " + fileName + 
                                   " Error: " + std::string(stbi_failure_reason())); ///< Throw on load failure
        }

        unsigned int texture;
        glGenTextures(1, &texture);       ///< Generate texture ID
        glBindTexture(GL_TEXTURE_2D, texture); ///< Bind texture
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); ///< Upload texture data
        glGenerateMipmap(GL_TEXTURE_2D); ///< Generate mipmaps for texture

        stbi_image_free(data); ///< Free image data

        sGetInstance()->m_textureMap[fileName] = texture; ///< Store texture ID in map
    }

    /**
     * @brief Private constructor for singleton pattern.
     * 
     * Sets default OpenGL texture parameters for wrapping and filtering.
     */
    TextureManager::TextureManager()
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); ///< Set horizontal wrapping to repeat
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); ///< Set vertical wrapping to repeat
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); ///< Set minification filter
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); ///< Set magnification filter
    }

    /**
     * @brief Destructor for cleaning up texture resources.
     * 
     * Deletes all OpenGL texture objects stored in the texture map.
     */
    TextureManager::~TextureManager() 
    {
        for (const auto& [name, id] : m_textureMap) 
        {
            if (id != 0) 
                glDeleteTextures(1, &id); ///< Free each texture ID
        }
    }

    /**
     * @brief Retrieves the singleton instance of TextureManager.
     * 
     * Creates the instance on first call with default texture parameters, then returns it on subsequent calls.
     * 
     * @return A shared pointer to the TextureManager instance.
     * @exception TextureException Thrown if instance creation fails due to an exception.
     */
    std::shared_ptr<TextureManager> TextureManager::sGetInstance() 
    {
        if (!ms_instance) 
        {
            try 
            {
                ms_instance = std::shared_ptr<TextureManager>(new TextureManager()); ///< Create instance
            } 
            catch (const std::exception& e) 
            {
                throw TextureException("Failed to create TextureManager instance: " + std::string(e.what())); ///< Rethrow with context
            }
        }
        return ms_instance;
    }
}