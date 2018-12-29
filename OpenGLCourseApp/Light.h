#pragma once

#include<GL/glew.h>
#include<glm/glm.hpp>

class Light
{
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat intensity,
		GLfloat xdir, GLfloat ydir, GLfloat zdir, GLfloat dIntensity);

	virtual void UseLight(GLuint ambientIntensityLoc, GLuint ambientColorLoc,
		GLuint diffuseIntensityLoc, GLuint directionLoc);

	~Light();

private:
	glm::vec3 color;
	GLfloat ambientIntensity;

	glm::vec3 direction;
	GLfloat diffuseIntensity;
};

