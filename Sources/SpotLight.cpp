#include "SpotLight.h"



SpotLight::SpotLight() :PointLight()
{
	direction = glm::vec3(0.0f, -1.0f, 0.0f);
	edge = 0.0f;
	procEdge = glm::cos(glm::radians(edge));
	isOn = true;
}

SpotLight::SpotLight(GLuint shadowWidth, GLuint shadowHeight,
	GLfloat near, GLfloat far,
	GLfloat red, GLfloat green, GLfloat blue,
	GLfloat intensity, GLfloat dIntensity,
	GLfloat xPos, GLfloat yPos, GLfloat zPos,
	GLfloat xDir, GLfloat yDir, GLfloat zDir,
	GLfloat con, GLfloat lin, GLfloat exp, GLfloat edg)
	:PointLight(shadowWidth, shadowHeight, near, far, red, green, blue, intensity, dIntensity, xPos, yPos, zPos, con, lin, exp)
{
	direction = glm::normalize(glm::vec3(xDir, yDir, zDir));
	edge = edg;
	procEdge = glm::cos(glm::radians(edge));
	isOn = true;
}


void SpotLight::UseLight(GLuint ambientIntensityLoc, GLuint ambientColorLoc, GLuint diffuseIntensityLoc,
	GLuint positionLoc, GLfloat directionLoc,
	GLuint constantLoc, GLuint linearLoc, GLuint coeffientLoc, GLuint edgeLoc)
{

	glUniform3f(ambientColorLoc, color.x, color.y, color.z);

	if (isOn)
	{
		glUniform1f(ambientIntensityLoc, ambientIntensity);
		glUniform1f(diffuseIntensityLoc, diffuseIntensity);
	}
	else
	{
		glUniform1f(ambientIntensityLoc, 0.0f);
		glUniform1f(diffuseIntensityLoc, 0.0f);
	}
	glUniform3f(positionLoc, position.x, position.y, position.z);
	glUniform1f(coeffientLoc, coefficient);
	glUniform1f(linearLoc, linear);
	glUniform1f(constantLoc, constant);

	glUniform3f(directionLoc, direction.x, direction.y, direction.z);
	glUniform1f(edgeLoc, procEdge);
}

void SpotLight::SetFlash(glm::vec3 pos, glm::vec3 dir)
{
	position = pos;
	direction = dir;
}

SpotLight::~SpotLight()
{
}
