#/bin/sh
g++ -o render-err-dev -std=c++17 main.cpp src/Renderer.cpp  src/Camera.cpp src/SimpleObject.cpp src/VertexBuffer.cpp src/VertexArray.cpp src/IndexBuffer.cpp src/Shader.cpp src/Texture.cpp src/Imports/stb_image/stb_image.cpp src/Imports/imgui/*.cpp src/Seens/BasicMovement.cpp -lglfw -lGLEW -lGL	
