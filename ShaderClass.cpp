#include "shaderClass.h"

// Reads a text file and outputs a string with everything in the text file
std::string get_file_contents(const char* _filename)
{
	std::ifstream in(_filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* _vertex_file, const char* _frag_file) {
	// Read vertexFile and fragmentFile and store the strings
	std::string vertex_code = get_file_contents(_vertex_file);
	std::string frag_code = get_file_contents(_frag_file);

	// Convert the shader source strings into character arrays
	const char* vertex_source = vertex_code.c_str();
	const char* frag_source = frag_code.c_str();

	// Shader setup
	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_source, NULL);
	glCompileShader(vertex_shader);

	GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag_shader, 1, &frag_source, NULL);
	glCompileShader(frag_shader);

	// Shader program
	shader_program_ID = glCreateProgram();
	glAttachShader(shader_program_ID, vertex_shader);
	glAttachShader(shader_program_ID, frag_shader);
	glLinkProgram(shader_program_ID);

	glDeleteShader(vertex_shader);
	glDeleteShader(frag_shader);

}

void Shader::activate() {
	glUseProgram(shader_program_ID);
}

void Shader::delete_shader() {
	glDeleteProgram(shader_program_ID);
}

