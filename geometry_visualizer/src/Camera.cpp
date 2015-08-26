//======GVis Libraries==========
#include <GVis/Camera.h>

//======Standard Libraries======
#include <vector>

//======OpenGL Related==========
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace gvis {

	// Constructor with glm vector
	Camera::Camera(glm::vec3 position /* = glm::vec3(0.0f, 0.0f, 0.0f) */, glm::vec3 up /* = glm::vec3(0.0f, 1.0f, 0.0f) */, GLfloat yaw /* = YAW */, GLfloat pitch /* = PITCH */)
		: Position(position), WorldUp(up), Yaw(yaw), Pitch(pitch),
		Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM)
	{
		updateCameraVectors();
	}


	// Constructor with scalar
	Camera::Camera(GLfloat pos_x /* = 0.0f */, GLfloat pos_y /* = 0.0f */, GLfloat pos_z /* = 0.0f */, GLfloat up_x /* = 0.0f */, GLfloat up_y /* = 1.0f */, GLfloat up_z /* = 0.0f */, GLfloat yaw /* = YAW */, GLfloat pitch /* = PITCH */)
		: Position(glm::vec3(pos_x, pos_y, pos_z)), WorldUp(glm::vec3(up_x, up_y, up_z)), Yaw(yaw), Pitch(pitch),
		Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM)
	{
		updateCameraVectors();
	}

	// Return the lookat matrix
	glm::mat4 Camera::GetViewMatrix() {
		return glm::lookAt(this->Position, this->Position + this->Front, this->Up);
	}


	// Process keyboard
	void Camera::ProcessKeyboard(CameraMovement direction, GLfloat time_interval) {
		GLfloat speed = this->MovementSpeed * time_interval;

		if (direction == FORWORD)
			this->Position += this->Front * speed;
		if (direction == BACKWARD)
			this->Position -= this->Front * speed;
		if (direction == LEFT)
			this->Position -= this->Right * speed;
	}


	// Process mouse movement
	void Camera::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean ban_flip /* = true */) {
		xoffset *= this->MouseSensitivity;
		yoffset *= this->MouseSensitivity;

		this->Yaw   += xoffset;
		this->Pitch += yoffset;

		// Prohibit pitch > 90 to prevent flip
		if (ban_flip) {
			if (this->Pitch > 89.0f)
				this->Pitch = 89.0f;
			if (this->Pitch < -89.0f)
				this->Pitch = -89.0f;
		}

		updateCameraVectors();
	}


	// Take mouse wheel offset as input to zoom
	void Camera::ProcessMouseScroll(GLfloat yoffset) {
		if (this->Zoom > 1.0f && this->Zoom <= 45.0f)
			this->Zoom -= yoffset;
		if (this->Zoom <= 1.0f)
			this->Zoom = 1.0f;
		if (this->Zoom >= 45.0f)
			this->Zoom = 45.0f;
	}


	// Update front, right and up vectors
	void Camera::updateCameraVectors() {
		glm::vec3 front;
		front.x = cos(glm::radians(this->Yaw) * cos(glm::radians(this->Pitch)));
		front.y = sin(glm::radians(this->Pitch));
		front.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));

		this->Front = glm::normalize(front);
		this->Right = glm::normalize(glm::cross(this->Front, this->WorldUp));
		this->Up    = glm::normalize(glm::cross(this->Right, this->Front));
	}

} // namespace gvis