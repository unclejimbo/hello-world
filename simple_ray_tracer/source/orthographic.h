#pragma once

#include "camera.h"

class Orthographic : public Camera
{
public:
	using Camera::Camera; // use base ctor
	~Orthographic() = default;
	void make_rays() override;
};