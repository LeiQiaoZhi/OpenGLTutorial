#include "UIApp.h"
#include "shaderClass.h";
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "Texture.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


const int WIDTH = 1600;
const int HEIGHT = 1600;
const float SCALE = 1;

// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
	-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
	 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
	 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
};

// Indices for vertices order
GLuint indices[] =
{
	0, 2, 1, // Upper triangle
	0, 3, 2 // Lower triangle
};

int main() {
	glfwInit();

	// tell GLFW we are using opengl 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// tell GLFW we are using the core profile
	// which only have modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create a window
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGLTutorial", NULL, NULL);
	// error checking
	if (window == NULL) {
		std::cout << "Failed to create glfw window." << std::endl;
		glfwTerminate();
		return -1;
	}
	// make the window into the current context (show it)
	glfwMakeContextCurrent(window);

	// load glad so it configures opengl
	gladLoadGL();

	// specify the viewport of OpenGL in the window
	glViewport(0, 0, WIDTH, HEIGHT);

	// create shader program
	Shader shader("default.vert", "default.frag");

	// set up vertex array object
	VAO vao;
	vao.bind();

	// create vertex buffer object to store vertices
	VBO vbo(vertices, sizeof(vertices));
	// create element buffer object to store indices
	EBO ebo(indices, sizeof(indices));

	// link vertex positions
	GLsizeiptr stride = 8 * sizeof(float);
	vao.link_attrib(vbo, 0, 3, GL_FLOAT, stride ,(void*)0);
	// link vertex attributes -- colors
	vao.link_attrib(vbo, 1, 3, GL_FLOAT, stride, (void*)(3 * sizeof(float)));
	vao.link_attrib(vbo, 2, 2, GL_FLOAT, stride, (void*)(6 * sizeof(float)));

	// unbind all to prevent accidentally modifying them
	vao.unbind();
	vbo.unbind();
	ebo.unbind();

	Texture popcat("Textures/popcat.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	popcat.pass_texture_to_shader(shader, "tex0", 0);

	UI::init(window, "#version 330");
	UI::UIPanel debugPanel("Debug");

	GLuint scale_uni_id = glGetUniformLocation(shader.shader_program_ID, "scale");

	// in a while loop so the window isn't closed immediately
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // set clear color to dark blue
		glClear(GL_COLOR_BUFFER_BIT); // clear bcak color buffer to the clear color

		// render triangle
		shader.activate();
		// set uniforms
		glUniform1f(scale_uni_id, SCALE);

		popcat.bind();
		vao.bind();
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		// UI
		debugPanel.show();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Delete all the objects we've created
	vao.delete_VAO();
	vbo.deleteBuffer();
	ebo.delete_buffer();
	popcat.delete_texture();
	shader.delete_shader();

	// ImGui shutdown
	UI::shutdown();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}