#pragma once

#include "VertexBufferLayout.hpp"
#include "kijuwGL.hpp"

class VertexArray{
private:

    unsigned int m_RenderID;

public:
    VertexArray();
    ~VertexArray();
    void Bind() const;
    void UnBind() const;

    void AddBuffer(const class VertexBuffer &vb, const VertexBufferLayout &Layout);


};

