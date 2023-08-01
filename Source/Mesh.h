#pragma once

#include "VAO.h"
#include "EBO.h"
#include "ShaderClass.h"
#include "Texture.h"
#include "CameraController.h"

#include <vector>

class Mesh {
public:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	VAO vao;

	Mesh(std::vector<Vertex> _vertices, std::vector<GLuint> _indices, std::vector<Texture> _textures);
	void draw(Shader& shader, CameraController& _camera_controller);
};