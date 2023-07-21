#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Reponsibilities:
// 1. Stores states
// 2. Calculates view and proj matrices
class Camera
{
protected:
	// states
	glm::vec3 position_;
	glm::vec3 forward_ = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 up_ = glm::vec3(0.0f, 1.0f, 0.0f);

public:
	Camera(glm::vec3 _position) : position_(_position) {}
	Camera(glm::vec3 _position, glm::vec3 _forward, glm::vec3 _up) : position_(_position), forward_(_forward), up_(_up) {}

	// getters
	glm::vec3 get_position() { return position_; }
	glm::vec3 get_forward() { return forward_; }
	glm::vec3 get_up() { return up_; }

	glm::mat4 compute_view_matrix();
	glm::mat4 compute_proj_matrix(int _width, int _height);

};
