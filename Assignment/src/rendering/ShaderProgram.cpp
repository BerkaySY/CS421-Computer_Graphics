#include "ShaderProgram.hpp"
#include <glad/glad.h>
#include <iostream>
#include <vector>
#include <fstream>


/**
 * @file ShaderProgram.cpp
 * @brief Implementation of the ShaderProgram class for managing OpenGL shader programs.
 */

namespace graf
{
    using namespace std;
    
    unordered_map<string, string> ShaderProgram::shaderCache; ///< Static cache for shader source files

    /**
     * @brief Creates a new OpenGL shader program.
     * 
     * Generates a new shader program object and stores its handle.
     */
    void ShaderProgram::Create()
    {
        m_id = glCreateProgram(); ///< Create program handle
    }

    /**
     * @brief Links the attached shaders into a complete program.
     * 
     * Links all attached shaders to form an executable shader program in OpenGL.
     */
    void ShaderProgram::Link()
    {
        glLinkProgram(m_id);
    }

    /**
     * @brief Activates the shader program for rendering.
     * 
     * Sets this shader program as the currently active one in the OpenGL context.
     */
    void ShaderProgram::Use()
    {
        glUseProgram(m_id);
    }

    /**
     * @brief Attaches a shader to the program.
     * 
     * Creates, compiles, and attaches a shader from a source file to the program.
     * If compilation fails, logs the error and cleans up without throwing an exception.
     * 
     * @param fileName The path to the shader source file (e.g., "vertex.glsl").
     * @param shaderType The type of shader (e.g., GL_VERTEX_SHADER, GL_FRAGMENT_SHADER).
     */
    void ShaderProgram::AttachShader(const string& fileName, unsigned int shaderType)    
    {
        unsigned int shaderId = glCreateShader(shaderType); ///< Create shader object

        string source = getShaderFromFile(fileName);

        const char* sourceTemp = &source[0];
        glShaderSource(shaderId, 1, &sourceTemp, NULL); ///< Set shader source code
        glCompileShader(shaderId);                      ///< Compile the shader
        
        GLint isCompiled = 0;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

            char* errorLog = new char[maxLength];
            glGetShaderInfoLog(shaderId, maxLength, &maxLength, &errorLog[0]);
            cout << "ShaderError:" << errorLog << endl; ///< Log compilation error
            
            glDeleteShader(shaderId); ///< Clean up shader object
            delete[] errorLog;        ///< Free error log memory
            return;                   ///< Exit without attaching
        }

        glAttachShader(m_id, shaderId); ///< Attach compiled shader to program
    }

    /**
     * @brief Loads shader source code from a file.
     * 
     * Checks the cache first; if not found, reads the file and caches the source.
     * 
     * @param fileName The path to the shader source file.
     * @return The shader source code as a string, or empty string if file cannot be opened.
     */
    string ShaderProgram::getShaderFromFile(const string& fileName) {
        auto it = shaderCache.find(fileName);
        if (it != shaderCache.end()) return it->second; ///< Return cached source

        ifstream file(fileName);
        string data;

        if (!file.is_open()) {
            cerr << "Error: Could not open shader file: " << fileName << endl;
            return ""; ///< Return empty string on failure
        }

        char readChar;
        while ((readChar = file.get()) != EOF)
            data += readChar; ///< Read file character by character
        file.close();

        shaderCache[fileName] = data; ///< Cache the source
        return data;
    }

    /**
     * @brief Adds a uniform variable to the program.
     * 
     * Retrieves the location of the specified uniform and stores it in the uniform map.
     * 
     * @param varName The name of the uniform variable in the shader code.
     */
    void ShaderProgram::AddUniform(const string& varName)
    {
        m_uniforms[varName] = glGetUniformLocation(m_id, varName.data());
    }

    /**
     * @brief Sets a float uniform value.
     * 
     * Updates the uniform if it exists in the program’s uniform map.
     * 
     * @param varName The name of the uniform variable.
     * @param value The float value to set.
     */
    void ShaderProgram::SetFloat(const string& varName, float value)
    {
        if (m_uniforms.count(varName) > 0)
        {
            unsigned int varLocation = m_uniforms[varName];
            glUniform1f(varLocation, value); ///< Set float uniform
        }
    }

    /**
     * @brief Sets a 4-component vector uniform value.
     * 
     * Updates the uniform if it exists in the program’s uniform map.
     * 
     * @param varName The name of the uniform variable.
     * @param value The glm::vec4 value to set (r, g, b, a components).
     */
    void ShaderProgram::SetVec4(const string& varName, const glm::vec4& value)
    {
        if (m_uniforms.count(varName) > 0)
        {
            unsigned int varLocation = m_uniforms[varName];
            glUniform4f(varLocation, value.r, value.g, value.b, value.a); ///< Set vec4 uniform
        }
    }    

    /**
     * @brief Sets a 3-component vector uniform value.
     * 
     * Updates the uniform if it exists in the program’s uniform map.
     * 
     * @param varName The name of the uniform variable.
     * @param value The glm::vec3 value to set (x, y, z components).
     */
    void ShaderProgram::SetVec3(const string& varName, const glm::vec3& value)
    {
        if (m_uniforms.count(varName) > 0)
        {
            unsigned int varLocation = m_uniforms[varName];
            glUniform3f(varLocation, value.x, value.y, value.z); ///< Set vec3 uniform
        }
    }   

    /**
     * @brief Sets a 4x4 matrix uniform value.
     * 
     * Updates the uniform if it exists in the program’s uniform map.
     * 
     * @param varName The name of the uniform variable.
     * @param value The glm::mat4 value to set (column-major order).
     */
    void ShaderProgram::SetMat4(const string& varName, const glm::mat4& value)
    {
        if (m_uniforms.count(varName) > 0)
        {
            unsigned int varLocation = m_uniforms[varName];
            glUniformMatrix4fv(varLocation, 1, false, &value[0][0]); ///< Set mat4 uniform
        }
    }
}