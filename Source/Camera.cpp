#include "Camera.h"

glm::mat4 Camera::compute_view_matrix()
{
	return glm::lookAt(position_, position_ + forward_, up_);
}

glm::mat4 Camera::compute_proj_matrix(int _width, int _height)
{
	glm::mat4 proj = glm::mat4(1.0f);
	proj = glm::perspective(glm::radians(45.0f), (float)_width / _height, 0.1f, 100.0f);
	return proj;
}

void Camera::move(float _d_right, float _d_up)
{
	position_ += _d_right * glm::normalize(glm::cross(forward_, up_));
	position_ += _d_up * up_;
}
