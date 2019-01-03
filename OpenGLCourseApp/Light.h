#pragma once

#include<GL/glew.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include "ShadowMap.h"

class Light
{
public:
	Light();
	Light(GLuint shadowWidth, GLuint shadowHeight,
		GLfloat red, GLfloat green, GLfloat blue,
		GLfloat intensity, GLfloat dIntensity);

	ShadowMap*  GetShadowMap() { return shadowMap; }

	virtual ~Light() = 0;

protected:
	glm::vec3 color;
	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;

	virtual void UseLight(GLuint ambientIntensityLoc, GLuint ambientColorLoc, GLuint diffuseIntensityLoc);

	glm::mat4 lightProj;
	ShadowMap* shadowMap;
};

