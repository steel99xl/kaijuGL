#/bin/sh

clear

echo "Building App..."

time clang++ -pipe -g -o MacWindow -std=c++17 -Wall -pedantic main.cpp src/Renderer.cpp src/Window.cpp src/FrameBufferObject.cpp src/SimplePhysics.cpp src/Camera.cpp src/SimpleObject.cpp src/VertexBuffer.cpp src/VertexArray.cpp src/IndexBuffer.cpp src/Shader.cpp src/Texture.cpp src/Imports/stb_image/stb_image.cpp  src/Seens/BasicMovement.cpp -lglfw -lGLEW -framework OpenGL 
