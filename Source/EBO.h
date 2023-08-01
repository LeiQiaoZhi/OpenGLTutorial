#pragma once

#include <glad/glad.h>
#include <vector>

class EBO {
public:
	GLuint ID;
	
	// we need size because vertices is a pointer, not an array
	EBO(std::vector<GLuint> _indices);

	void bind();
	void unbind();
	void delete_buffer();

};

