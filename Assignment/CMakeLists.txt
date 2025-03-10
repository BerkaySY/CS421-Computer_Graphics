cmake_minimum_required(VERSION 3.5)
include(CMakePrintHelpers)

string(FIND ${CMAKE_CURRENT_SOURCE_DIR} / StartingIndex REVERSE)
math(EXPR StartingIndex "${StartingIndex}+1")
string(SUBSTRING ${CMAKE_CURRENT_SOURCE_DIR} ${StartingIndex} -1 ProjectName)

project(${ProjectName})

set(Project_Dir ${CMAKE_SOURCE_DIR})
set(Thirdparty_Dir ${Project_Dir}/Thirdparty)

set(Project_Include_Dir ${Project_Dir}/include)
set(Project_Src_Dir ${Project_Dir}/src)


set(Core_Source_Files
    ${Project_Src_Dir}/core/GLWindow.cpp
)

set(Rendering_Source_Files
    ${Project_Src_Dir}/rendering/VertexArrayObject.cpp
    ${Project_Src_Dir}/rendering/VertexBuffer.cpp
    ${Project_Src_Dir}/rendering/IndexBuffer.cpp
    ${Project_Src_Dir}/rendering/ShaderProgram.cpp
    ${Project_Src_Dir}/rendering/TextureManager.cpp
)

set(Factory_Source_Files
    ${Project_Src_Dir}/factory/ShapeFactory.cpp
    ${Project_Src_Dir}/factory/ShapeFactoryManager.cpp
    ${Project_Src_Dir}/factory/CircleFactory.cpp
    ${Project_Src_Dir}/factory/CubeFactory.cpp
    ${Project_Src_Dir}/factory/FrustumFactory.cpp
    ${Project_Src_Dir}/factory/PyramidFactory.cpp
    ${Project_Src_Dir}/factory/SquareFactory.cpp
)

set(External_Source_Files
    ${Project_Src_Dir}/glad/glad.c
)

set(Project_Source_Files 
    ${Project_Src_Dir}/main.cpp
    ${Core_Source_Files}
    ${Rendering_Source_Files}
    ${Factory_Source_Files}
    ${External_Source_Files}
)

include_directories(
    ${Project_Include_Dir}
    ${Project_Include_Dir}/core
    ${Project_Include_Dir}/rendering
    ${Project_Include_Dir}/factory
    ${Thirdparty_Dir}/glm
    ${Thirdparty_Dir}
    ${Thirdparty_Dir}/stb
    ${Thirdparty_Dir}/json
)

set(glfw3_DIR ${Thirdparty_Dir}/GLFW/lib/cmake/glfw3/)
find_package(glfw3 3.4 REQUIRED)

add_executable(${PROJECT_NAME} ${Project_Source_Files})
target_link_libraries(${PROJECT_NAME} glfw)