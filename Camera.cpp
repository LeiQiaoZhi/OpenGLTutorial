#include "Camera.h"

glm::mat4 Camera::compute_view_matrix()
{
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, -position_);
	// TODO: rotate view matrix
	return view;
}

glm::mat4 Camera::compute_proj_matrix(int _width, int _height)
{
	glm::mat4 proj = glm::mat4(1.0f);
	proj = glm::perspective(glm::radians(45.0f), (float)_width / _height, 0.1f, 100.0f);
	return proj;
}
