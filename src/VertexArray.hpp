#pragma once

#include "VertexBufferLayout.hpp"
#include "KaijuRenderWarnings.hpp"

//#include "kaijuGL.hpp"

class VertexArray{
protected:

    unsigned int m_RenderID;

public:
    VertexArray();
    ~VertexArray();
    void Bind() const;
    void UnBind() const;

    void AddBuffer(const class VertexBuffer &vb, const VertexBufferLayout &Layout);


};

