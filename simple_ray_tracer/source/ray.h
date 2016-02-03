#pragma once

#include <glm/vec3.hpp>

class Ray
{
public:
	Ray() = default;
	Ray(const glm::vec3& position, const glm::vec3& direction) :
		_pos(position), _dir(direction)
	{
	}
	~Ray() = default;

	void set_pos(const glm::vec3&);
	void set_dir(const glm::vec3&);
	glm::vec3 get_pos() const;
	glm::vec3 get_dir() const;
private:
	glm::vec3 _pos;
	glm::vec3 _dir;
};

inline void Ray::set_pos(const glm::vec3& position)
{
	_pos = position;
}

inline void Ray::set_dir(const glm::vec3& direction)
{
	_dir = direction;
}

inline glm::vec3 Ray::get_pos() const
{
	return _pos;
}

inline glm::vec3 Ray::get_dir() const
{
	return _dir;
}