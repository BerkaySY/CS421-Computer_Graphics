#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

/**
 * @file ShaderProgram.hpp
 * @brief Defines the ShaderProgram class for managing OpenGL shader programs.
 */

namespace graf
{
    using namespace std;
    
    /**
     * @class ShaderProgram
     * @brief A class for creating and managing OpenGL shader programs.
     * 
     * This class encapsulates the creation, attachment, linking, and usage of shader programs
     * in OpenGL. It supports loading shaders from files, managing uniform variables, and
     * setting their values for rendering.
     */
    class ShaderProgram
    {
    public:
        /**
         * @brief Creates a new OpenGL shader program.
         * 
         * Initializes an empty shader program object in the OpenGL context.
         */
        void Create();

        /**
         * @brief Attaches a shader to the program.
         * 
         * Loads, compiles, and attaches a shader from a file to the shader program.
         * 
         * @param fileName The path to the shader source file (e.g., ".glsl").
         * @param shadertype The type of shader (e.g., GL_VERTEX_SHADER, GL_FRAGMENT_SHADER).
         * @exception ShaderException Thrown if shader compilation fails.
         */
        void AttachShader(const string& fileName, unsigned int shadertype);

        /**
         * @brief Adds a uniform variable to the program.
         * 
         * Retrieves and stores the location of a uniform variable for later use.
         * 
         * @param varName The name of the uniform variable in the shader code.
         */
        void AddUniform(const string& varName);

        /**
         * @brief Links the attached shaders into a complete program.
         * 
         * Finalizes the shader program by linking all attached shaders.
         * @exception ShaderException Thrown if linking fails (not directly here, but in practice).
         */
        void Link();

        /**
         * @brief Activates the shader program for rendering.
         * 
         * Sets this shader program as the current one in the OpenGL context.
         */
        void Use();

        /**
         * @brief Sets a float uniform value.
         * @param varName The name of the uniform variable.
         * @param value The float value to set.
         */
        void SetFloat(const string& varName, float value);

        /**
         * @brief Sets a 4-component vector uniform value.
         * @param varName The name of the uniform variable.
         * @param value The glm::vec4 value to set.
         */
        void SetVec4(const string& varName, const glm::vec4& value);

        /**
         * @brief Sets a 3-component vector uniform value.
         * @param varName The name of the uniform variable.
         * @param value The glm::vec3 value to set.
         */
        void SetVec3(const string& varName, const glm::vec3& value);

        /**
         * @brief Sets a 4x4 matrix uniform value.
         * @param varName The name of the uniform variable.
         * @param value The glm::mat4 value to set.
         */
        void SetMat4(const string& varName, const glm::mat4& value);
        
    private:
        /**
         * @brief Loads shader source code from a file.
         * 
         * Reads the shader source from the specified file, caching it for reuse.
         * 
         * @param fileName The path to the shader source file.
         * @return The shader source code as a string, or empty if loading fails.
         */
        string getShaderFromFile(const string& fileName);

    private:
        unsigned int m_id;                        ///< OpenGL handle for the shader program.
        unordered_map<string, unsigned int> m_uniforms; ///< Map of uniform names to their locations.
        static unordered_map<string, string> shaderCache; ///< Cache of loaded shader source code.
    };
}