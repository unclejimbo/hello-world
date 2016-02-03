#pragma once

#include "surface.h"

class Sphere : public Surface
{
public:
	Sphere(glm::vec3 center, float radius) :
		_center(center), _radius(radius)
	{
	}
	~Sphere() = default;

	bool hit(const Ray& r, float t0, float t1, Hit_Record& record) override;
	Box bbox() const override;
private:
	glm::vec3 _center;
	float _radius;
};