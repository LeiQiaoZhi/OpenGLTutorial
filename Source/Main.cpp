#include "UIApp.h"
#include "Mesh.h"

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
glm::vec3 light_pos = glm::vec3(0.0f, 0.5f, 0.0f);

// Vertices coordinates
Vertex vertices[] =
{ //               COORDINATES           /            Normals          /           Colors         /       TEXTURE COORDINATES    //
	Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3
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

	Texture textures[]{
	Texture((dir_path + "\\Textures\\planks.png").c_str(), Texture::Type::Diffuse, 0, GL_RGBA, GL_UNSIGNED_BYTE),
	Texture((dir_path + "\\Textures\\planksSpec.png").c_str(), Texture::Type::Specular, 1, GL_RED, GL_UNSIGNED_BYTE)
	};

	// vector constructor takes start and end iterators
	std::vector<Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector<GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector<Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));

	Mesh floor(verts, ind, tex);

	UI::init(window, "#version 330");
	UI::UIPanel debugPanel("Debug");

	// set constant uniforms
	shader.activate();
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
	Camera camera(glm::vec3(0.0f, 0.5f, -2.0f));
	CameraController camera_controller(&camera, WIDTH, HEIGHT);

	// in a while loop so the window isn't closed immediately
	while (!glfwWindowShouldClose(window)) {
		// background color
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // set clear color to dark blue
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear back color buffer to the clear color

		// set uniforms
		glUniform1f(scale_uni_id, SCALE);

		// rotation 
		double current_time = glfwGetTime();
		if (current_time - prev_time > 1 / 120) {
			//rotation += 0.5f;
			prev_time = current_time;
		}

		glm::mat4 world = glm::mat4(1.0f);
		world = glm::rotate(world, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		// send matrices to shader
		int world_id = glGetUniformLocation(shader.program_ID, "world");
		glUniformMatrix4fv(world_id, 1, GL_FALSE, glm::value_ptr(world));


		camera_controller.handle_inputs(window);

		floor.draw(shader, camera_controller);

		// UI
		debugPanel.show();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	shader.delete_shader();

	// ImGui shutdown
	UI::shutdown();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}