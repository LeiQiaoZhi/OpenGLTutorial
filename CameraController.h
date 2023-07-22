#pragma once
#include <glad/glad.h>	
#include <GLFW/glfw3.h>
#include "Camera.h"

class CameraController
{
private:
	Camera* camera_;

	// settings
	float move_speed_ = 1.0f;
	float rotate_speed_ = 1.0f;
	bool invert_x_ = true;
	bool invert_y_ = true;

	const int width_;
	const int height_;

	// states
	bool first_mouse_ = true;
	double last_x_ = width_ / 2.0f;
	double last_y_ = height_ / 2.0f;

public:
	CameraController(Camera* _camera, int _width, int _height) : camera_(_camera), width_(_width), height_(_height) {}

	void handle_inputs(GLFWwindow* _window);

	// operations
	void pan(float _dx, float _dy);
	void orbit(float _angle_x, float _angle_y);

	glm::mat4 compute_view_matrix() { return camera_->compute_view_matrix(); }
	glm::mat4 compute_proj_matrix() { return camera_->compute_proj_matrix(width_, height_); }

};
