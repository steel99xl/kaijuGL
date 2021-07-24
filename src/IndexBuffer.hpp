//
// Created by steel99xl on 6/14/21.
//
#pragma once
#include "Engine.hpp"

class IndexBuffer{
private:
    unsigned int  m_RenderID;
    unsigned int m_Count;
    unsigned int m_Unquie;
public:
    IndexBuffer(const unsigned int *data, unsigned int count);
    ~IndexBuffer();

    void Bind() const;
    void UnBind() const;

    inline unsigned int GetCount () const {return m_Count; }
    inline unsigned int Unquie() const {return m_Unquie; }
};




