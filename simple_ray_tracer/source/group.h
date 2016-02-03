#pragma once

#include <memory>
#include <vector>

#include "surface.h"

using surface_ptr = std::unique_ptr<Surface> ;

class Group : public Surface
{
public:
	Group() {}
	~Group() {}

	bool hit(const Ray& r, float t0, float t1, Hit_Record& record) override;
	Box bbox() const override;

	void push_back(surface_ptr&& sptr);
	void pop_back();
private:
	std::vector<surface_ptr> _surfaces;
};