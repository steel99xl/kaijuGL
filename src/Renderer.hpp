//
// Created by steel99xl on 6/14/21.
//

#pragma once

#include "kaijuGL.hpp"

/*
#include <GL/glew.h>
#include <iostream>
#include <cstring>
#include <functional>
#include <unordered_set>
#include <memory>
#include <vector>
#include <array>
#include "Imports/glm/glm.hpp"
#include "Imports/glm/gtc/matrix_transform.hpp"
#include "Imports/imgui/imgui.h"
#include "Imports/imgui/imgui_impl_glfw.h"
#include "Imports/imgui/imgui_impl_opengl3.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "IndexBuffer.h"
#include "Shader.h"

*/





#define GLCall(function); GLClearError(); function; GLLogCall(#function, __FILE__, __LINE__);

// Get error event from gpu
void GLClearError();

void GLLogCall(const char *function, const char *file, int line);

class Renderer{

protected:

public:

    Renderer();
    ~Renderer();

    void Clear() const;

    void Draw(class VertexArray &va, class IndexBuffer &ib, class Shader &shader);

};

