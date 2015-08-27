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
		: Position_(position), WorldUp_(up), Yaw_(yaw), Pitch_(pitch),
		Front_(glm::vec3(0.0f, 0.0f, -1.0f)), Speed_(SPEED), Sensitivity_(SENSITIVTY), Zoom_(ZOOM)
	{
		updateCameraVectors();
	}


	// Constructor with scalar
	Camera::Camera(GLfloat pos_x /* = 0.0f */, GLfloat pos_y /* = 0.0f */, GLfloat pos_z /* = 0.0f */, GLfloat up_x /* = 0.0f */, GLfloat up_y /* = 1.0f */, GLfloat up_z /* = 0.0f */, GLfloat yaw /* = YAW */, GLfloat pitch /* = PITCH */)
		: Position_(glm::vec3(pos_x, pos_y, pos_z)), WorldUp_(glm::vec3(up_x, up_y, up_z)), Yaw_(yaw), Pitch_(pitch),
		Front_(glm::vec3(0.0f, 0.0f, -1.0f)), Speed_(SPEED), Sensitivity_(SENSITIVTY), Zoom_(ZOOM)
	{
		updateCameraVectors();
	}

	// Return the lookat matrix
	glm::mat4 Camera::GetViewMatrix() {
		return glm::lookAt(this->Position_, this->Position_ + this->Front_, this->Up_);
	}


	// Process keyboard
	void Camera::ProcessKeyboard(CameraMovement direction, GLfloat time_interval) {
		GLfloat speed = this->Speed_ * time_interval;

		if (direction == FORWORD)
			this->Position_ += this->Front_ * speed;
		if (direction == BACKWARD)
			this->Position_ -= this->Front_ * speed;
		if (direction == LEFT)
			this->Position_ -= this->Right_ * speed;
	}


	// Process mouse movement
	void Camera::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean ban_flip /* = true */) {
		xoffset *= this->Sensitivity_;
		yoffset *= this->Sensitivity_;

		this->Yaw_   += xoffset;
		this->Pitch_ += yoffset;

		// Prohibit pitch > 90 to prevent flip
		if (ban_flip) {
			if (this->Pitch_ > 89.0f)
				this->Pitch_ = 89.0f;
			if (this->Pitch_ < -89.0f)
				this->Pitch_ = -89.0f;
		}

		updateCameraVectors();
	}


	// Take mouse wheel offset as input to zoom
	void Camera::ProcessMouseScroll(GLfloat yoffset) {
		if (this->Zoom_ > 1.0f && this->Zoom_ <= 45.0f)
			this->Zoom_ -= yoffset;
		if (this->Zoom_ <= 1.0f)
			this->Zoom_ = 1.0f;
		if (this->Zoom_ >= 45.0f)
			this->Zoom_ = 45.0f;
	}


	// Update front, right and up vectors
	void Camera::updateCameraVectors() {
		glm::vec3 front;
		front.x = cos(glm::radians(this->Yaw_) * cos(glm::radians(this->Pitch_)));
		front.y = sin(glm::radians(this->Pitch_));
		front.z = sin(glm::radians(this->Yaw_)) * cos(glm::radians(this->Pitch_));

		this->Front_ = glm::normalize(front);
		this->Right_ = glm::normalize(glm::cross(this->Front_, this->WorldUp_));
		this->Up_    = glm::normalize(glm::cross(this->Right_, this->Front_));
	}

} // namespace gvis