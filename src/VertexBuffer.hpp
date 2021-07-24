//
// Created by steel99xl on 6/14/21.
//
#pragma once

#include "Engine.hpp"

class VertexBuffer{
private:
    unsigned int  m_RenderID;
public:
    VertexBuffer(const void *data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void UnBind() const;

    inline unsigned int GetBufferID() { return m_RenderID; };
};





