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

	if (keys[GLFW_KEY_W])
	{
		position += front * velocity;
	}

	if (keys[GLFW_KEY_S])
	{
		position -= front * velocity;
	}

	if (keys[GLFW_KEY_A])
	{
		position -= right * velocity;
	}

	if (keys[GLFW_KEY_D])
	{
		position += right * velocity;
	}
}

void Camera::joyStickControl(const unsigned char* buttons, const float* axes, GLfloat deltaTime)
{

	if (buttons == NULL)
		return;

	GLfloat velocity = moveSpeed * deltaTime;

	if (buttons[GLFW_GAMEPAD_BUTTON_DPAD_UP] == GLFW_PRESS)
	{
		position += front * velocity;
	}

	if (buttons[GLFW_GAMEPAD_BUTTON_DPAD_DOWN] == GLFW_PRESS)
	{
		position -= front * velocity;
	}

	if (buttons[GLFW_GAMEPAD_BUTTON_DPAD_LEFT] == GLFW_PRESS)
	{
		position -= right * velocity;
	}

	if (buttons[GLFW_GAMEPAD_BUTTON_DPAD_RIGHT] == GLFW_PRESS)
	{
		position += right * velocity;
	}

	if (axes == NULL)
		return;

	if (axes[GLFW_GAMEPAD_AXIS_LEFT_Y] < -0.5f)
	{
		position += front * velocity;
	}

	if (axes[GLFW_GAMEPAD_AXIS_LEFT_Y] > 0.5f)
	{
		position -= front * velocity;
	}

	if (axes[GLFW_GAMEPAD_AXIS_LEFT_X] < -0.5f)
	{
		position -= right * velocity;
	}

	if (axes[GLFW_GAMEPAD_AXIS_LEFT_X] > 0.5f)
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


Camera::~Camera()
{
}
