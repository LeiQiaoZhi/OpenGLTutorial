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
	float zoom_speed_ = 0.1f; // between 0 and 1
	bool invert_x_ = true;
	bool invert_y_ = true;

	const int width_;
	const int height_;

	// states
	glm::vec3 target_ = glm::vec3(0.0f);
	bool first_mouse_ = true;
	double last_x_ = width_ / 2.0f;
	double last_y_ = height_ / 2.0f;

public:
	CameraController(Camera* _camera, int _width, int _height) : camera_(_camera), width_(_width), height_(_height) {}

	void handle_inputs(GLFWwindow* _window);
	void scroll_callback(GLFWwindow* _window, double _x_offset, double _y_offset);

	// operations
	void pan(float _dx, float _dy);
	void orbit(float _angle_x, float _angle_y);
	void zoom(float zoom_factor);

	glm::mat4 compute_view_matrix() { return camera_->compute_view_matrix(); }
	glm::mat4 compute_proj_matrix() { return camera_->compute_proj_matrix(width_, height_); }

};
