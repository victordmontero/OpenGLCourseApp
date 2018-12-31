#include "SpotLight.h"



SpotLight::SpotLight() :PointLight()
{
	direction = glm::vec3(0.0f, -1.0f, 0.0f);
	edge = 0.0f;
	procEdge = glm::cos(glm::radians(edge));
}

SpotLight::SpotLight(GLfloat red, GLfloat green, GLfloat blue,
	GLfloat intensity, GLfloat dIntensity,
	GLfloat xPos, GLfloat yPos, GLfloat zPos,
	GLfloat xDir, GLfloat yDir, GLfloat zDir,
	GLfloat con, GLfloat lin, GLfloat exp, GLfloat edg)
	:PointLight(red, green, blue, intensity, dIntensity, xPos, yPos, zPos, con, lin, exp)
{
	direction = glm::normalize(glm::vec3(xDir, yDir, zDir));
	edge = edg;
	procEdge = glm::cos(glm::radians(edge));
}


void SpotLight::UseLight(GLuint ambientIntensityLoc, GLuint ambientColorLoc, GLuint diffuseIntensityLoc,
	GLuint positionLoc, GLfloat directionLoc,
	GLuint constantLoc, GLuint linearLoc, GLuint coeffientLoc, GLuint edgeLoc)
{
	PointLight::UseLight(ambientIntensityLoc, ambientColorLoc, diffuseIntensityLoc,
		positionLoc, constantLoc, linearLoc, coeffientLoc);
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
