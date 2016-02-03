#include <vector>
#include <iostream>

#include <EasyBMP/EasyBMP.h>

#include <glm/vec3.hpp>

#include "orthographic.h"
#include "perspective.h"
#include "sphere.h"
#include "group.h"
#include "light.h"

const int g_width = 800;
const int g_height = 600;

int main()
{
	std::unique_ptr<Surface> ball{ new Sphere{ glm::vec3(0.0, 0.0f, -300.0), 150.0 } };
	std::unique_ptr<Surface> ball2{ new Sphere{ glm::vec3(500.0, 100.0, -600.0), 200.0 } };
	Group group;
	group.push_back(std::move(ball));
	group.push_back(std::move(ball2));

	BMP image;
	image.SetSize(g_width, g_height);
	image.SetBitDepth(32);

	Light point_light{ glm::vec3(-100.0, 250.0, 0.0), 
		glm::vec3(255, 255, 255), 1.0 };

	glm::vec3 diffuse_coefficient{ 255, 0, 0 };
	glm::vec3 specular_coefficient{ 255, 255, 255 };
	int phong_exponet = 100;
	float ambient_intensity = 0.05;
	glm::vec3 ambient_coefficient{ diffuse_coefficient };

	glm::vec3 diffuse_coefficient2{ 0, 0, 255 };
	int phong_exponet2 = 20;
	glm::vec3 ambient_coefficient2{ diffuse_coefficient2 };

	// Orthographic camera
	Orthographic othographic_camera;
	othographic_camera.make_rays();

	for (int i = 0; i < g_width; ++i) {
		for (int j = 0; j < g_height; ++j) {
			Hit_Record hit_rec;
			auto &rayp = othographic_camera(i, j);
			if (group.hit(*rayp, 10.0, 1000.0, hit_rec)) {
				// Shading ball
				glm::vec3 normal{ hit_rec.normal };
				glm::vec3 intersection{ rayp->get_pos() + hit_rec.t * rayp->get_dir() };
				glm::vec3 light{ glm::normalize(point_light.position - intersection) };
				float cos_theta = glm::dot(normal, light);
				cos_theta = cos_theta > 0 ? cos_theta : 0;
				glm::vec3 diffuse_color{ diffuse_coefficient * point_light.intensity * cos_theta };

				glm::vec3 view{ -glm::normalize(intersection) };
				glm::vec3 half{ glm::normalize(light + view) };
				float phong = glm::dot(normal, half);
				phong = phong > 0 ? std::pow(phong, phong_exponet) : 0;
				glm::vec3 specular_color = specular_coefficient * point_light.intensity * phong;

				glm::vec3 ambient_color = ambient_intensity * ambient_coefficient;

				glm::vec3 output_color{ diffuse_color + specular_color + ambient_color};

				image(i, j)->Red = output_color.r < 255 ? output_color.r : 255;
				image(i, j)->Green = output_color.g < 255 ? output_color.g : 255;
				image(i, j)->Blue = output_color.b < 255 ? output_color.b : 255;
				image(i, j)->Alpha = 0;
			} else {
				glm::vec3 background_color{ 30, 30, 30 };
				image(i, j)->Red = background_color.r;
				image(i, j)->Green = background_color.g;
				image(i, j)->Blue = background_color.b;
				image(i, j)->Alpha = 0;
			}
		}
	}

	image.WriteToFile("orthographic.bmp");

	// Perspective camera
	Perspective perspective_camera;
	perspective_camera.set_height(2000.0);
	perspective_camera.zoom(0.1);
	perspective_camera.make_rays();

	for (int i = 0; i < g_width; ++i) {
		for (int j = 0; j < g_height; ++j) {
			Hit_Record hit_rec;
			auto &rayp = perspective_camera(i, j);
			if (group.hit(*rayp, 0.1, 1000.0, hit_rec)) {
				// Shading ball
				glm::vec3 normal{ hit_rec.normal };
				glm::vec3 intersection{ rayp->get_pos() + hit_rec.t * rayp->get_dir() };
				glm::vec3 light{ glm::normalize(point_light.position - intersection) };
				float cos_theta = glm::dot(normal, light);
				cos_theta = cos_theta > 0 ? cos_theta : 0;
				glm::vec3 diffuse_color{ diffuse_coefficient * point_light.intensity * cos_theta };

				glm::vec3 view{ -glm::normalize(intersection) };
				glm::vec3 half{ glm::normalize(light + view) };
				float phong = glm::dot(normal, half);
				phong = phong > 0 ? std::pow(phong, phong_exponet) : 0;
				glm::vec3 specular_color = specular_coefficient * point_light.intensity * phong;

				glm::vec3 ambient_color = ambient_intensity * ambient_coefficient;

				glm::vec3 output_color{ diffuse_color + specular_color + ambient_color };

				image(i, j)->Red = output_color.r < 255 ? output_color.r : 255;
				image(i, j)->Green = output_color.g < 255 ? output_color.g : 255;
				image(i, j)->Blue = output_color.b < 255 ? output_color.b : 255;
				image(i, j)->Alpha = 0;
			} else {
				glm::vec3 background_color{ 30, 30, 30 };
				image(i, j)->Red = background_color.r;
				image(i, j)->Green = background_color.g;
				image(i, j)->Blue = background_color.b;
				image(i, j)->Alpha = 0;
			}
		}
	}
	image.WriteToFile("perspective.bmp");

	return 0;
}