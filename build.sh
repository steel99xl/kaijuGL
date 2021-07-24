#/bin/sh
g++ -o Window -std=c++17 main.cpp src/Renderer.cpp src/VertexBuffer.cpp src/VertexArray.cpp src/IndexBuffer.cpp src/Shader.cpp src/Texture.cpp src/Imports/stb_image/stb_image.cpp src/Imports/imgui/*.cpp src/Tests/TestClearColor.cpp -lglfw -lGLEW -lGL	
