#include "EBO.h"

EBO::EBO(std::vector<GLuint> _indices)
{
	glGenBuffers(1, &ID);
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(GLuint), _indices.data(), GL_STATIC_DRAW);
}

// make the buffer known as the active EBO
void EBO::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::delete_buffer()
{
	glDeleteBuffers(1, &ID);
}
