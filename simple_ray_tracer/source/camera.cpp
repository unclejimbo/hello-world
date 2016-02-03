#include "camera.h"

Camera::Camera()
{
	for (int i = 0; i < _res_v; ++i) {
		for (int j = 0; j < _res_u; ++j) {
			ray_ptr rayp(new Ray);
			_rays.push_back(std::move(rayp));
		}
	}
}

Camera::Camera(const glm::vec3& position, const glm::vec3& rightward, const glm::vec3& upward,
			   const int resolution_x, const int resolution_y, const float width, const float height)
{
	_pos = position;
	_u = glm::normalize(rightward);
	_v = glm::normalize(upward);
	_w = glm::normalize(glm::cross(_u, _v));
	_res_u = resolution_x;
	_res_v = resolution_y;
	_width = width;
	_height = height;

	for (int i = 0; i < _res_v; ++i) {
		for (int j = 0; j < _res_u; ++j) {
			ray_ptr rayp(new Ray);
			_rays.push_back(std::move(rayp));
		}
	}
}

const ray_ptr& Camera::operator()(int i, int j)
{
	auto &r = _rays[i * _res_v + j];
	return r;
}

inline Camera::const_iterator Camera::ray_begin() const
{
	return _rays.begin();
}

inline Camera::const_iterator Camera::ray_end() const
{
	return _rays.end();
}

inline size_t Camera::ray_count() const
{
	return _res_u * _res_v;
}