#include "UIApp.h"
#include "shaderClass.h";
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "Texture.h"
#include "Camera.h"
#include "CameraController.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

std::string dir_path = fs::current_path().parent_path().string();
std::string src_path = dir_path + "\\Source";

const int WIDTH = 1600;
const int HEIGHT = 1600;
const float SCALE = 1;

glm::vec4 light_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
glm::vec3 light_pos = glm::vec3(0.5f, 0.5f, 0.5f);

// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, // Left Side

	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f, // Right side

	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f  // Facing side
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2, // Bottom side
	0, 2, 3, // Bottom side
	4, 6, 5, // Left side
	7, 9, 8, // Non-facing side
	10, 12, 11, // Right side
	13, 15, 14 // Facing side
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
	Shader shader((src_path + "\\Others\\default.vert").c_str(), (src_path + "\\Others\\default.frag").c_str());

	// set up vertex array object
	VAO vao;
	vao.bind();

	// create vertex buffer object to store vertices
	VBO vbo(vertices, sizeof(vertices));
	// create element buffer object to store indices
	EBO ebo(indices, sizeof(indices));

	// link vertex positions
	GLsizeiptr stride = 11 * sizeof(float);
	vao.link_attrib(vbo, 0, 3, GL_FLOAT, stride, (void*)0);
	vao.link_attrib(vbo, 1, 3, GL_FLOAT, stride, (void*)(3 * sizeof(float))); // colors
	vao.link_attrib(vbo, 2, 2, GL_FLOAT, stride, (void*)(6 * sizeof(float))); // tex coords
	vao.link_attrib(vbo, 3, 3, GL_FLOAT, stride, (void*)(8 * sizeof(float))); // normals

	// unbind all to prevent accidentally modifying them
	vao.unbind();
	vbo.unbind();
	ebo.unbind();

	Texture texture((dir_path + "\\Textures\\brick.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	texture.pass_texture_to_shader(shader, "tex0", 0);

	UI::init(window, "#version 330");
	UI::UIPanel debugPanel("Debug");

	GLuint scale_uni_id = glGetUniformLocation(shader.program_ID, "scale");
	GLuint light_color_uni_id = glGetUniformLocation(shader.program_ID, "lightColor");
	GLuint light_pos_uni_id = glGetUniformLocation(shader.program_ID, "lightPos");
	glUniform4f(light_color_uni_id, light_color.x, light_color.y, light_color.z, light_color.w);
	glUniform3f(light_pos_uni_id, light_pos.x, light_pos.y, light_pos.z);

	// Enables the Depth Buffer (z-buffer)
	glEnable(GL_DEPTH_TEST);

	// Variables that help the rotation of the pyramid
	float rotation = 0.0f;
	double prev_time = glfwGetTime();

	// create camera
	Camera camera(glm::vec3(0.0f, 0.0f, -1.0f));
	CameraController camera_controller(&camera, WIDTH, HEIGHT);

	// in a while loop so the window isn't closed immediately
	while (!glfwWindowShouldClose(window)) {
		// background color
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // set clear color to dark blue
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear back color buffer to the clear color

		// render triangle
		shader.activate();
		// set uniforms
		glUniform1f(scale_uni_id, SCALE);

		// rotation 
		double current_time = glfwGetTime();
		if (current_time - prev_time > 1 / 120) {
			//rotation += 0.5f;
			prev_time = current_time;
		}

		// initialize matrices
		glm::mat4 world = glm::mat4(1.0f);

		// set up matrices
		world = glm::rotate(world, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));

		// send matrices to shader
		int world_id = glGetUniformLocation(shader.program_ID, "world");
		int view_id = glGetUniformLocation(shader.program_ID, "view");
		int proj_id = glGetUniformLocation(shader.program_ID, "proj");
		GLuint cam_pos_id = glGetUniformLocation(shader.program_ID, "camPos");
		glUniformMatrix4fv(world_id, 1, GL_FALSE, glm::value_ptr(world));
		glUniformMatrix4fv(view_id, 1, GL_FALSE, glm::value_ptr(camera_controller.compute_view_matrix()));
		glUniformMatrix4fv(proj_id, 1, GL_FALSE, glm::value_ptr(camera_controller.compute_proj_matrix()));
		auto cam_pos = camera_controller.get_position();
		glUniform3f(cam_pos_id, cam_pos.x, cam_pos.y, cam_pos.z);

		camera_controller.handle_inputs(window);

		texture.bind();
		vao.bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		// UI
		debugPanel.show();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Delete all the objects we've created
	vao.delete_VAO();
	vbo.deleteBuffer();
	ebo.delete_buffer();
	texture.delete_texture();
	shader.delete_shader();

	// ImGui shutdown
	UI::shutdown();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}