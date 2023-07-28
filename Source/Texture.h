#pragma once
#include <glad/glad.h>
#include <stb/stb_image.h>

#include "ShaderClass.h"

class Texture {
public:
	GLuint texture_object_ID;
	GLuint type;

	Texture(const char* _image, GLenum _type, GLenum _slot, GLenum _format, GLenum _pixel_type);

	void pass_texture_to_shader(Shader& _shader, const char* uniform, GLuint _texture_unit);
	void bind();
	void unbind();
	void delete_texture();
};
