#pragma once

//======Standard Libraries======
#include <vector>

//======OpenGL Related==========
#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace gvis {

	// Abstract camera movement
	enum CameraMovement {
		FORWORD,
		BACKWARD,
		LEFT,
		RIGHT
	};

	// Default camera attributes
	const GLfloat YAW        = -90.0f;
	const GLfloat PITCH      = 0.0f;
	const GLfloat SPEED      = 3.0f;
	const GLfloat SENSITIVTY = 0.25f;
	const GLfloat ZOOM       = 45.0f;

	class Camera {
	public:
		// Camera attributes
		glm::vec3   Position_;
		glm::vec3   Front_;
		glm::vec3   Up_;
		glm::vec3   Right_;
		glm::vec3   WorldUp_;
		GLfloat     Yaw_;
		GLfloat     Pitch_;
		GLfloat     Speed_;
		GLfloat     Sensitivity_;
		GLfloat     Zoom_;

		
		Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH);
		Camera(GLfloat pos_x = 0.0f, GLfloat pos_y = 0.0f, GLfloat pos_z = 0.0f, GLfloat up_x = 0.0f, GLfloat up_y = 1.0f, GLfloat up_z = 0.0f, GLfloat yaw = YAW, GLfloat pitch = PITCH);
		Camera() = default;
		~Camera() {}

		glm::mat4 GetViewMatrix();
		void ProcessKeyboard(CameraMovement direction, GLfloat time_interval);
		void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean ban_flip = true);
		void ProcessMouseScroll(GLfloat yoffset);

	private:
		void updateCameraVectors();
	};

} // namespace gvis