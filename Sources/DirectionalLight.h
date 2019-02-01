#pragma once

#include "Light.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight();

	DirectionalLight(GLuint shadowWidth, GLuint shadowHeight, 
		GLfloat red, GLfloat green, GLfloat blue,
		GLfloat intensity, GLfloat dIntensity,
		GLfloat xdir, GLfloat ydir, GLfloat zdir);

	virtual void UseLight(GLuint ambientIntensityLoc, GLuint ambientColorLoc,
		GLuint diffuseIntensityLoc, GLuint directionLoc);

	glm::mat4 CalculateLightTransform();

	~DirectionalLight();

private:
	glm::vec3 direction;
};

