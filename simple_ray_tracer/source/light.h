#pragma once

#include <glm/vec3.hpp>

struct Light
{
	glm::vec3 position;
	glm::vec3 color;
	float intensity;
};