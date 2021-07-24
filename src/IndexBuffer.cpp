#include "IndexBuffer.hpp"


IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count) : m_Count(count), m_Unquie(sizeof(data)){

		GLCall(glGenBuffers(1, &m_RenderID));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count , data, GL_STATIC_DRAW));

}

IndexBuffer::~IndexBuffer(){
	GLCall(glDeleteBuffers(1, &m_RenderID));
}

void IndexBuffer::Bind() const {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID));
}

void IndexBuffer::UnBind() const {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
