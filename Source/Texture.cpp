#include "Texture.h"

Texture::Texture(const char* _image, GLenum _type, GLenum _slot, GLenum _format, GLenum _pixel_type)
{
	type = _type;

	// Load image
	int width, height, num_channels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* image_bytes = stbi_load(_image, &width, &height, &num_channels, 0);

	// Generate texture object
	glGenTextures(1, &texture_object_ID);
	// Activate texture unit
	glActiveTexture(_slot);
	// Bind texture object to active texture unit
	glBindTexture(type, texture_object_ID);

	// Set texture parameters
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Set texture wrapping
	glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Load image data to texture object
	glTexImage2D(type, 0, GL_RGBA, width, height, 0, _format, _pixel_type, image_bytes);
	glGenerateMipmap(type);

	stbi_image_free(image_bytes);
	// Unbind texture
	glBindTexture(type, 0);
}

void Texture::pass_texture_to_shader(Shader& _shader, const char* uniform, GLuint _texture_unit)
{
	GLuint texture_uniform = glGetUniformLocation(_shader.program_ID, uniform);
	_shader.activate();
	// pass texture from texture unit to shader
	glUniform1i(texture_uniform, _texture_unit);
}

void Texture::bind()
{
	glBindTexture(type, texture_object_ID);
}

void Texture::unbind()
{
	glBindTexture(type, 0);
}

void Texture::delete_texture()
{
	glDeleteTextures(1, &texture_object_ID);
}



