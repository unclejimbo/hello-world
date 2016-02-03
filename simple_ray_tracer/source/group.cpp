#include "group.h"

bool Group::hit(const Ray& r, float t0, float t1, Hit_Record& record)
{
	Hit_Record rec;
	bool first_hit = true;
	bool is_hit = false;
	for (auto &s : _surfaces) {
		if (s->hit(r, t0, t1, rec)) {
			is_hit = true;
			if (first_hit) {
				record = rec;
				first_hit = false;
			}
			if (rec.t < record.t && !first_hit)
				record = rec;
		}
	}
	return is_hit;
}

Box Group::bbox() const
{
	Box bound;
	bool first = true;
	for (auto &s : _surfaces) {
		if (first) {
			bound = s->bbox();
		} else {
			Box box = s->bbox();
			bound.left = box.left < bound.left ? box.left : bound.left;
			bound.right = box.right > bound.right ? box.right : bound.right;
			bound.top = box.top > bound.top ? box.top : bound.top;
			bound.bottom = box.bottom < bound.bottom ? box.bottom : bound.bottom;
		}
	}
	return bound;
}


void Group::push_back(surface_ptr&& sptr)
{
	_surfaces.push_back(std::move(sptr));
}

void Group::pop_back()
{
	_surfaces.pop_back();
}