//
// Created by steel99xl on 6/14/21.
//
#pragma once

#include "kijuwGL.hpp"

class VertexBuffer{
private:
    unsigned int  m_RenderID;
public:
    VertexBuffer();
    ~VertexBuffer();

    void MakeDynamicBuffer(const void *data, unsigned int size);
    void MakeStaticBuffer(const void *data, unsigned int size);

    void Bind() const;
    void UnBind() const;

    inline unsigned int GetBufferID() { return m_RenderID; };
};





