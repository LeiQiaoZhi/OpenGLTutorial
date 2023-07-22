#include "CameraController.h"
#include <iostream>

void CameraController::handle_inputs(GLFWwindow* _window)
{
	// get mouse pos
	double x_pos, y_pos;
	glfwGetCursorPos(_window, &x_pos, &y_pos);

	if (first_mouse_)
	{
		last_x_ = x_pos;
		last_y_ = y_pos;
		first_mouse_ = false;
		return;
	}

	float min_dimension = std::min(width_, height_);
	float dx = -(int)invert_x_ * (x_pos - last_x_) / min_dimension;
	float dy = -(int)invert_y_ * (last_y_ - y_pos) / min_dimension;

	if (dx == 0 && dy == 0)
		return;

	// Handles mouse inputs
	if (glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		orbit(dx, dy);
	else if (glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
		pan(dx, dy);
	else if (glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE
		|| glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_RELEASE)
		first_mouse_ = true;

	last_x_ = x_pos;
	last_y_ = y_pos;
}

void CameraController::pan(float _dx, float _dy)
{
	//std::cout << "pan x:" << _dx << " y:" << _dy << std::endl;
	camera_->move(_dx * move_speed_, _dy * move_speed_);
}

void CameraController::orbit(float _angle_x, float _angle_y)
{
	std::cout << "orbit x:" << _angle_x << " y:" << _angle_y << std::endl;
}
