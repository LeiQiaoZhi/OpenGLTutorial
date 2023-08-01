#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

// a struct containing vertex attributes
struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 tex_uv;
};


class VBO {
public:
	GLuint ID;
	
	VBO(std::vector<Vertex>& vertices);

	void bind();
	void unbind();
	void deleteBuffer();

};
