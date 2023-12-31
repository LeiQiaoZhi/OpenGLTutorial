#include "Texture.h"

Texture::Texture(const char* _image, Type _type, GLenum _slot, GLenum _format, GLenum _pixel_type)
{
	type = _type;
	slot = _slot;

	// Load image
	int width, height, num_channels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* image_bytes = stbi_load(_image, &width, &height, &num_channels, 0);

	// Generate texture object
	glGenTextures(1, &texture_object_ID);
	// Activate texture unit, GL_TEXTURE0 is the first texture unit
	glActiveTexture(GL_TEXTURE0 + _slot);
	// Bind texture object to active texture unit
	glBindTexture(GL_TEXTURE_2D, texture_object_ID);

	// Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Set texture wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Load image data to texture object
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, _format, _pixel_type, image_bytes);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(image_bytes);
	// Unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
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
	// Activate the texture unit that the texture is binding to
	glActiveTexture(GL_TEXTURE0 + slot);
	// Bind texture object to active texture unit
	glBindTexture(GL_TEXTURE_2D, texture_object_ID);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::delete_texture()
{
	glDeleteTextures(1, &texture_object_ID);
}



