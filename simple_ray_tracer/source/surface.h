#pragma  once

#include <glm/vec3.hpp>

#include "ray.h"

struct Box
{
	float left;
	float right;
	float bottom;
	float top;
};

struct Hit_Record
{
	float t;
	glm::vec3 normal;
};

class Surface
{
public:
	virtual ~Surface() {}
	virtual bool hit(const Ray& r, float t0, float t1, Hit_Record& record) = 0;
	virtual Box bbox() const = 0;
};