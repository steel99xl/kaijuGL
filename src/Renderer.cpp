//
// Created by steel99xl on 6/14/21.
//
#include "Renderer.hpp"

void GLClearError(){
    while(glGetError() != GL_NO_ERROR);
}

void GLLogCall(const char *function, const char *file, int line){
    while(GLenum error = glGetError()){
        std::cout << "[OpenGL Error] "<< error << " "<< function << " " << file << " " << line <<  std::endl;
        //std::cout << gluErrorString(error) << std::endl;
    }
}

Renderer::Renderer(){};

Renderer::~Renderer(){};

void Renderer::Clear() const {
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(class VertexArray &va, class IndexBuffer &ib, class Shader &shader) {
    va.Bind();
    ib.Bind();
    shader.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
