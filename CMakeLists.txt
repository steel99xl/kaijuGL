cmake_minimum_required(VERSION 3.19)
project(GLWindow)

find_package(OpenGL REQUIRED)
find_package(glfw3)

set(GL_LIBRARY "-GL")
set(GLFW_LIBRARY "-lglfw")
set(GLEW_LIBRARY "-lGLEW")
set(MAC_MAGIC "-framework OpenGL")

set(CMAKE_CXX_STANDARD 14)
add_executable(GLWindow main.cpp Renderer.h Renderer.cpp)

target_link_libraries(GLWindow ${GL_LIBRARY} ${GLFW_LIBRARY} ${GLEW_LIBRARY})
