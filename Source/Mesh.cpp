#include "Mesh.h"
#include <glm/gtc/type_ptr.hpp>

Mesh::Mesh(std::vector<Vertex> _vertices, std::vector<GLuint> _indices, std::vector<Texture> _textures)
{
	// TODO: use move
	vertices = _vertices;
	indices = _indices;
	textures = _textures;

	vao.bind();
	VBO vbo(vertices);
	EBO ebo(indices);

	vao.link_attrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	vao.link_attrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	vao.link_attrib(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	vao.link_attrib(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));

	vao.unbind();
	vbo.unbind();
	ebo.unbind();
}

void Mesh::draw(Shader& shader, CameraController& _camera_controller)
{
	shader.activate();
	vao.bind();

	size_t diffuse_count = 0;
	size_t specular_count = 0;
	// every texture has an unique uniform name and texture unit 
	for (size_t i = 0; i < textures.size(); i++)
	{
		switch (textures[i].type)
		{
		case Texture::Type::Diffuse:
			textures[i].pass_texture_to_shader(shader,
				("diffuse" + std::to_string(diffuse_count)).c_str(), i);
			diffuse_count++;
			break;
		case Texture::Type::Specular:
			textures[i].pass_texture_to_shader(shader,
				("specular" + std::to_string(specular_count)).c_str(), i);
			specular_count++;
			break;
		default:
			break;
		}
		textures[i].bind();
	}

	// pass matrices
	int view_id = glGetUniformLocation(shader.program_ID, "view");
	int proj_id = glGetUniformLocation(shader.program_ID, "proj");
	glUniformMatrix4fv(view_id, 1, GL_FALSE, glm::value_ptr(_camera_controller.compute_view_matrix()));
	glUniformMatrix4fv(proj_id, 1, GL_FALSE, glm::value_ptr(_camera_controller.compute_proj_matrix()));

	int cam_pos_id = glGetUniformLocation(shader.program_ID, "camPos");
	auto cam_pos = _camera_controller.get_position();
	glUniform3f(cam_pos_id, cam_pos.x, cam_pos.y, cam_pos.z);

	// draw mesh
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}