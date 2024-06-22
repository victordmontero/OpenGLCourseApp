
extern "C"
{
#include <SDL.h>
}

#include "Camera.h"

Camera::Camera() {}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
{
	position = startPosition;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	moveSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;

	update();
}

void Camera::keyControl(bool* keys, GLfloat deltaTime)
{
	GLfloat velocity = moveSpeed * deltaTime;

	if (keys[SDLK_e])
	{
		position += front * velocity;
	}

	if (keys[SDLK_d])
	{
		position -= front * velocity;
	}

	if (keys[SDLK_s])
	{
		position -= right * velocity;
	}

	if (keys[SDLK_f])
	{
		position += right * velocity;
	}
}

void Camera::joyStickControl(const unsigned char* buttons, const float* axes, GLfloat deltaTime)
{

	if (buttons == NULL)
		return;

	GLfloat velocity = moveSpeed * deltaTime;

	if (buttons[SDL_CONTROLLER_BUTTON_DPAD_UP] == SDL_TRUE)
	{
		position += front * velocity;
	}

	if (buttons[SDL_CONTROLLER_BUTTON_DPAD_DOWN] == SDL_TRUE)
	{
		position -= front * velocity;
	}

	if (buttons[SDL_CONTROLLER_BUTTON_DPAD_LEFT] == SDL_TRUE)
	{
		position -= right * velocity;
	}

	
	if (buttons[SDL_CONTROLLER_BUTTON_DPAD_RIGHT] == SDL_TRUE)
	{
		position += right * velocity;
	}

	if (axes == nullptr)
		return;

	if (axes[SDL_CONTROLLER_AXIS_LEFTY] < -1.5f)
	{
		position += front * velocity;
	}

	if (axes[SDL_CONTROLLER_AXIS_LEFTY] > 1.5f)
	{
		position -= front * velocity;
	}

	if (axes[SDL_CONTROLLER_AXIS_LEFTX] < -1.5f)
	{
		position -= right * velocity;
	}

	if (axes[SDL_CONTROLLER_AXIS_LEFTX] > 1.5f)
	{
		position += right * velocity;
	}
}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange)
{
	xChange *= turnSpeed;
	yChange *= turnSpeed;

	yaw += xChange;
	pitch += yChange;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}

	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	update();
}

glm::mat4 Camera::calculateViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

void Camera::update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

glm::vec3 Camera::getCameraPosition()
{
	return position;
}

glm::vec3 Camera::getCameraDirection()
{
	return glm::normalize(front);
}


Camera::~Camera()
{
}
