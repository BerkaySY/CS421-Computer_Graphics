#define GLFW_INCLUDE_NONE
#define STB_IMAGE_IMPLEMENTATION

#include "GLWindow.hpp"
#include "ShaderProgram.hpp"
#include "VertexArrayObject.hpp"
#include "TextureManager.hpp"
#include "Exceptions.hpp"
#include "ErrorCheck.hpp"
#include "ShapeFactoryManager.hpp"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

/**
 * @file main.cpp
 * @brief Main entry point for demo application.
 * 
 * This program rendering multiple 3D shapes with textures in a grid layout, 
 * featuring keyboard interaction to move and change the shape of an active object.
 */

/**
 * @struct ObjectData
 * @brief Stores properties of a renderable 3D object.
 */
struct ObjectData 
{
    glm::vec3 position;            ///< 3D position of the object in world space.
    float angle = 0.0f;            ///< Rotation angle around the Y-axis in degrees.
    std::string texture;           ///< File path of the texture applied to the object.
    graf::ShapeTypes shape = graf::ShapeTypes::Cube; ///< Type of shape (e.g., Cube, Pyramid).
};

//Function Prototypes
void saveObjectsToJson(const std::vector<ObjectData>& objects, const std::string& filename);
std::vector<ObjectData> loadObjectsFromJson(const std::string& filename);
void DrawObject(graf::ShaderProgram& program, std::shared_ptr<graf::VertexArrayObject> p_va,
                const glm::vec3& position, float angle, float scale,
                const glm::mat4& matProj, const std::string& texture);

/**
 * @brief Main application entry point.
 * 
 * Initializes the OpenGL window, shader program, textures, and a grid of objects,
 * then enters a render loop with keyboard interaction.
 * 
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return Exit status: 0 for success, -1 for failure.
 */
int main(int argc, char** argv) 
{
    try 
    {
        graf::GLWindow glwindow;
        glwindow.create(800, 800); ///< Create 800x800 OpenGL window

        graf::ShapeFactoryManager shapeFactoryManager; ///< Manager for creating shapes

        graf::ShaderProgram program;
        program.Create(); ///< Initialize shader program

        try 
        {
            program.AttachShader("../shaders/vertex.glsl", GL_VERTEX_SHADER); ///< Load vertex shader
            program.AttachShader("../shaders/fragment.glsl", GL_FRAGMENT_SHADER); ///< Load fragment shader
            program.Link(); ///< Link shaders into program
            program.AddUniform("uWorldTransform"); ///< Add uniform for world transform matrix
        }
        catch (const graf::ShaderException& e) 
        {
            std::cerr << "Shader initialization failed: " << e.what() << std::endl;
            return -1; ///< Exit on shader failure
        }

        std::vector<std::string> textures = {
            "../images/container.jpg",
            "../images/container2.jpg",
            "../images/container3.jpg",
            "../images/container4.jpg"
        }; ///< List of texture file paths

        try 
        {
            for (const auto& texture : textures) 
                graf::TextureManager::sAddTextureFromFile(texture); ///< Load all textures
        }
        catch (const graf::TextureException& e) 
        {
            std::cerr << "Texture loading failed: " << e.what() << std::endl;
            return -1; ///< Exit on texture failure
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, textures.size() - 1); ///< Random distribution for texture selection

        glm::mat4 matProj = glm::perspective(glm::radians(90.0f), 1.0f, 1.0f, 100.0f); ///< 90-degree FOV projection matrix

        const std::string file_path = "objectdatas.json";
        std::vector<ObjectData> objects = loadObjectsFromJson(file_path); ///< Load objects from JSON file

        if (objects.empty())
        {
            objects = {
                {{-2.0f,  2.0f, -3.0f}}, {{0.0f,  2.0f, -3.0f}}, {{2.0f,  2.0f, -3.0f}}, ///< Top row
                {{-2.0f,  0.0f, -3.0f}}, {{0.0f,  0.0f, -3.0f}}, {{2.0f,  0.0f, -3.0f}}, ///< Middle row
                {{-2.0f, -2.0f, -3.0f}}, {{0.0f, -2.0f, -3.0f}}, {{2.0f, -2.0f, -3.0f}}  ///< Bottom row
            }; ///< 3x3 grid of objects
    
            for (auto& obj : objects)
                obj.texture = textures[dist(gen)]; ///< Assign random texture to each object
        }
        

        float scale = 1.0f;  ///< Uniform scale factor for all objects
        int activeIndex = 4; ///< Index of the initially active object (center)

        glwindow.SetKeyboardFunction([&](int key, int scancode, int action) {
            if (action == GLFW_PRESS) 
            {
                if (key >= GLFW_KEY_0 && key <= GLFW_KEY_8) activeIndex = key - GLFW_KEY_0; ///< Select active object (0-8)

                if (key == GLFW_KEY_UP)    objects[activeIndex].position.y += 0.1f; ///< Move up
                if (key == GLFW_KEY_DOWN)  objects[activeIndex].position.y -= 0.1f; ///< Move down
                if (key == GLFW_KEY_LEFT)  objects[activeIndex].position.x -= 0.1f; ///< Move left
                if (key == GLFW_KEY_RIGHT) objects[activeIndex].position.x += 0.1f; ///< Move right

                if (key == GLFW_KEY_SPACE) ///< Cycle through shape types
                {
                    if (objects[activeIndex].shape == graf::ShapeTypes::Cube)
                        objects[activeIndex].shape = graf::ShapeTypes::Square;
                    else if (objects[activeIndex].shape == graf::ShapeTypes::Square)
                        objects[activeIndex].shape = graf::ShapeTypes::Circle;
                    else if (objects[activeIndex].shape == graf::ShapeTypes::Circle)
                        objects[activeIndex].shape = graf::ShapeTypes::Pyramid;
                    else if (objects[activeIndex].shape == graf::ShapeTypes::Pyramid)
                        objects[activeIndex].shape = graf::ShapeTypes::Frustum;
                    else if (objects[activeIndex].shape == graf::ShapeTypes::Frustum)
                        objects[activeIndex].shape = graf::ShapeTypes::Cube;    
                }
            }
        });
        
        glwindow.SetRenderFunction([&]() {
            try
            {
                glClearColor(0.0f, 0.4f, 0.7f, 1.0f); ///< Set background color (sky blue)
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); ///< Clear color and depth buffers
                graf::CheckGLError("Clear buffers"); ///< Check for OpenGL errors

                program.Use(); ///< Activate shader program
                for (size_t i = 0; i < objects.size(); ++i) 
                {
                    if (i == activeIndex) objects[i].angle += 0.01f; ///< Rotate active object
                    DrawObject(program, shapeFactoryManager.createShape(objects[i].shape),
                            objects[i].position, objects[i].angle, scale, matProj, objects[i].texture); ///< Draw each object
                }
            }
            catch (const std::exception& e) 
            {
                std::cerr << "Render error: " << e.what() << std::endl;
            }
        });

        glwindow.SetCloseFunction([&]() {
            saveObjectsToJson(objects, file_path); ///< Save objects to JSON file on window close
        });
        glwindow.Render();  ///< Start the rendering loop
        exit(EXIT_SUCCESS); ///< Exit successfully
    }
    catch (const graf::GLWindowException& e) 
    {
        std::cerr << "Window error: " << e.what() << std::endl;
        return -1; ///< Exit on window failure
    }
    catch (const graf::GrafException& e) 
    {
        std::cerr << "Graphics error: " << e.what() << std::endl;
        return -1; ///< Exit on graphics failure
    }
    catch (const std::exception& e) 
    {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
        return -1; ///< Exit on unexpected failure
    }    
}

/**
 * @brief Saves the state of objects to a JSON file.
 * 
 * @param objects Vector of ObjectData containing the objects to save.
 * @param filename The path to the JSON file where data will be saved.
 */
void saveObjectsToJson(const std::vector<ObjectData>& objects, const std::string& filename) 
{
    json j;
    for (const auto& obj : objects) 
    {
        j.push_back({
            {"position_x", obj.position.x},
            {"position_y", obj.position.y},
            {"position_z", obj.position.z},
            {"angle", obj.angle},
            {"texture", obj.texture},
            {"shape_type", static_cast<int>(obj.shape)}
        });
    }

    std::ofstream file(filename);
    if (file.is_open()) 
    {
        file << std::setw(4) << j << std::endl;
        file.close();
    }
    else 
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
}

/**
 * @brief Loads the state of objects from a JSON file.
 * 
 * @param filename The path to the JSON file to read from.
 * @return Vector of ObjectData loaded from the file, or empty if loading fails.
 */
std::vector<ObjectData> loadObjectsFromJson(const std::string& filename) 
{
    std::vector<ObjectData> objects;
    std::ifstream file(filename);
    if (!file.is_open()) 
    {
        std::cerr << "Failed to open file for reading: " << filename << std::endl;
        return objects; ///< Return empty vector on failure
    }

    json j;
    try 
    {
        file >> j;
        for (const auto& item : j) 
        {
            ObjectData obj;
            obj.position.x = item["position_x"].get<float>();
            obj.position.y = item["position_y"].get<float>();
            obj.position.z = item["position_z"].get<float>();
            obj.angle = item["angle"].get<float>();
            obj.texture = item["texture"].get<std::string>();
            obj.shape = static_cast<graf::ShapeTypes>(item["shape_type"].get<int>());
            objects.push_back(obj);
        }
    }
    catch (const json::exception& e) 
    {
        std::cerr << "JSON parsing error: " << e.what() << std::endl;
    }

    file.close();
    return objects;
}

/**
 * @brief Renders a single 3D object with transformations and texture.
 * 
 * Applies translation, rotation, and scaling transformations to the object,
 * sets the shader uniform, binds the texture, and draws the object.
 * 
 * @param program The shader program to use for rendering.
 * @param p_va Shared pointer to the VertexArrayObject representing the object’s geometry.
 * @param position The object’s position in 3D space.
 * @param angle The rotation angle around the Y-axis in degrees.
 * @param scale The uniform scale factor for the object.
 * @param matProj The projection matrix for perspective rendering.
 * @param texture The file path of the texture to apply.
 * @exception BufferException Thrown if the VAO is null.
 * @exception std::exception Caught broadly for any other rendering errors.
 */
void DrawObject(graf::ShaderProgram& program, std::shared_ptr<graf::VertexArrayObject> p_va,
                const glm::vec3& position, float angle, float scale,
                const glm::mat4& matProj, const std::string& texture) 
{
    try
    {
        if (!p_va) 
            throw graf::BufferException("Null vertex array object"); ///< Validate VAO
        
        p_va->Bind(); ///< Bind VAO for rendering
        glm::mat4 matTranslate = glm::translate(glm::mat4(1), position); ///< Translation matrix
        glm::mat4 matRotation = glm::rotate(glm::mat4(1), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f)); ///< Rotation matrix (Y-axis)
        glm::mat4 matScale = glm::scale(glm::mat4(1), glm::vec3(scale, scale, 1.0f)); ///< Scaling matrix
        glm::mat4 matWorld = matTranslate * matRotation * matScale; ///< Combined world transform

        program.SetMat4("uWorldTransform", matProj * matWorld); ///< Set shader uniform
        graf::TextureManager::sActivateTexture(texture); ///< Bind texture
        p_va->Draw(); ///< Draw the object

        p_va->Unbind(); ///< Unbind VAO
    }
    catch (const std::exception& e) 
    {
        std::cerr << "Draw object failed: " << e.what() << std::endl;
    }
}