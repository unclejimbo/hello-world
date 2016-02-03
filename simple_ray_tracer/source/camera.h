#pragma once

#include <memory>
#include <vector>
#include <iterator>

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

#include "ray.h"

using ray_ptr = std::unique_ptr<Ray>;

class Camera
{
public:
	Camera();
	Camera(const glm::vec3& position, 
		   const glm::vec3& rightward, 
		   const glm::vec3& upward,
		   const int resolution_x, const int resolution_y, 
		   const float width, const float height);
	virtual ~Camera() {}

	const ray_ptr& operator()(int i, int j); // BMP coordinate

	virtual void make_rays() = 0;

	using const_iterator = std::vector<ray_ptr>::const_iterator;
	virtual const_iterator ray_begin() const;
	virtual const_iterator ray_end() const;
	virtual size_t ray_count() const;

	void set_width(float w);
	void set_height(float h);
protected:
	// position
	glm::vec3 _pos{ glm::vec3(0.0) };

	// directions
	glm::vec3 _u{ glm::vec3(1.0, 0.0, 0.0) }; // rightward
	glm::vec3 _v{ glm::vec3(0.0, 1.0, 0.0) }; // upward
	glm::vec3 _w{ glm::vec3(0.0, 0.0, 1.0) }; // inward

	// resolution
	int _res_u{ 800.0f };
	int _res_v{ 600.0f };

	// view plane
	float _width{ 800.0f };
	float _height{ 600.0f };

	// vector of ray_ptrs
	std::vector<ray_ptr> _rays;
private:
	float ratio = 0.75;
};

inline void Camera::set_width(float w)
{
	_width = w;
	_height = _width * ratio;
}

inline void Camera::set_height(float h)
{
	_height = h;
	_width = _height / ratio;
}