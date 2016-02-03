#include "orthographic.h"

void Orthographic::make_rays()
{
	float left = -_width / 2;
	float top = _height / 2;

	// BMP coordinate
	for (int i = 0; i < _res_u; ++i) {
		for (int j = 0; j < _res_v; ++j) {
			float x = left + _width * (i + 0.5) / _res_u;
			float y = top - _height * (j + 0.5) / _res_v;
			glm::vec3 position{ _pos + x*_u + y*_v };
			_rays[i * _res_v + j]->set_pos(position);
			_rays[i * _res_v + j]->set_dir(-glm::normalize(_w));
		}
	}
}