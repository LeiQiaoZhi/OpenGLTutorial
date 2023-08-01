#pragma once
#include <glad/glad.h>
#include <stb/stb_image.h>

#include "ShaderClass.h"

class Texture {

public:
	enum class Type {
		Diffuse, Specular
	};
	GLuint texture_object_ID;
	Type type;
	GLenum slot; // the texture unit the texture is binding to

	Texture(const char* _image, Type _type, GLenum _slot, GLenum _format, GLenum _pixel_type);

	void pass_texture_to_shader(Shader& _shader, const char* uniform, GLuint _texture_unit);
	void bind();
	void unbind();
	void delete_texture();
};
