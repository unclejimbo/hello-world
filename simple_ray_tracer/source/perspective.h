#pragma once

#include "camera.h"

class Perspective : public Camera
{
public:
	using Camera::Camera; // use base ctor
	~Perspective() = default;
	void make_rays() override;

	void zoom(float len);
private:
	float _focus{_height};
};

inline void Perspective::zoom(float len)
{
	float ratio = len / _focus;
	_focus = len;
	_width *= ratio;
	_height *= ratio;
}