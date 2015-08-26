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
		glm::vec3   Position;
		glm::vec3   Front;
		glm::vec3   Up;
		glm::vec3   Right;
		glm::vec3   WorldUp;
		GLfloat     Yaw;
		GLfloat     Pitch;
		GLfloat     MovementSpeed;
		GLfloat     MouseSensitivity;
		GLfloat     Zoom;

		
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