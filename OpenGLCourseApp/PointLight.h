#pragma once
#include<vector>

#include "Light.h"

#include "OmniShadowMap.h"

class PointLight :
	public Light
{
public:
	PointLight();
	PointLight(GLuint shadowWidth, GLuint shadowHeight,
		GLfloat near, GLfloat far,
		GLfloat red, GLfloat green, GLfloat blue,
		GLfloat intensity, GLfloat dIntensity,
		GLfloat xPos, GLfloat yPos, GLfloat zPos,
		GLfloat con, GLfloat lin, GLfloat exp);

	virtual void UseLight(GLuint ambientIntensityLoc, GLuint ambientColorLoc, GLuint diffuseIntensityLoc,
		GLuint positionLoc, GLuint constantLoc, GLuint linearLoc, GLuint coeffientLoc);

	std::vector<glm::mat4> CalculateLightTransform();

	GLfloat GetFarPlane();
	glm::vec3 GetPosition();

	~PointLight();

protected:
	glm::vec3 position;
	GLfloat constant, linear, coefficient;

	GLfloat farPlane;
};

