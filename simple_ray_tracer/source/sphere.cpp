#include "sphere.h" 

#include <limits>
#include <cmath>

#include <glm/geometric.hpp>

bool Sphere::hit(const Ray& r, float t0, float t1, Hit_Record& record)
{
	glm::vec3 pos = r.get_pos();
	glm::vec3 dir = r.get_dir();

	// intermediate results
	float dd = glm::dot(dir, dir);
	glm::vec3 p_minus_c = pos - _center;
	float pmc = glm::dot(p_minus_c, p_minus_c);
	float dpmc = glm::dot(dir, p_minus_c);

	float delta = dpmc * dpmc - dd * (pmc - _radius * _radius);
	const float eps = std::numeric_limits<float>::epsilon();
	if (delta < - eps) {
		// no intersection
		return false;
	} else if (delta > - eps && delta < eps) {
		// one intersection
		record.t = -dpmc / dd;
	} else {
		// two intersections, return smaller one
		record.t = (-dpmc - std::sqrt(delta)) / dd;
	}
	glm::vec3 intersect = pos + record.t * dir;
	record.normal = glm::normalize(intersect - _center);
	return true;

}

Box Sphere::bbox() const
{
	Box temp;
	temp.left   = _center.x - _radius;
	temp.right  = _center.x + _radius;
	temp.bottom = _center.y - _radius;
	temp.top    = _center.y + _radius;
	return temp;
}