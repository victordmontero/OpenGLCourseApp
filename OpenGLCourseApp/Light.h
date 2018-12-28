#pragma once

#include<GL/glew.h>
#include<glm/glm.hpp>

class Light
{
public:
	/*Light();*/
	Light(GLfloat red=1.0f, GLfloat green = 1.0f, GLfloat blue = 1.0f, GLfloat intensity = 1.0f);

	virtual void UseLight(GLfloat ambientIntensityLoc,GLfloat ambientColorLoc);

	~Light();

private:
	glm::vec3 color;
	GLfloat ambientIntensity;
};

