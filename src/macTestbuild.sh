#/bin/sh
g++ -o MacTestWindow -std=c++17 mainTests.cpp src/Renderer.cpp src/VertexBuffer.cpp src/VertexArray.cpp src/IndexBuffer.cpp src/Shader.cpp src/Texture.cpp src/Imports/stb_image/stb_image.cpp src/Imports/imgui/*.cpp src/Tests/test.cpp src/Tests/TestClearColor.cpp src/Tests/TestTexture2d.cpp src/Tests/TestBatchRender.cpp src/Tests/TestBatchStreamData.cpp -lglfw -lGLEW  -framework OpenGL
