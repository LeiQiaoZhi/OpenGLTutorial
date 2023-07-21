#pragma once
#include <glad/glad.h>	
#include <GLFW/glfw3.h>
#include "Camera.h"

class CameraController
{
private:
	Camera* camera_;

	float move_speed_;
	float rotate_speed_;

	const int width_ = 1600;
	const int height_ = 900;

public:
	CameraController(Camera* _camera, float _move_speed, float _rotate_speed, int _width, int _height) : camera_(_camera), move_speed_(_move_speed), rotate_speed_(_rotate_speed), width_(_width), height_(_height) {}

	void handle_inputs(GLFWwindow* _window);

	glm::mat4 compute_view_matrix() { return camera_->compute_view_matrix(); }
	glm::mat4 compute_proj_matrix() { return camera_->compute_proj_matrix(width_, height_); }

};
