#include "Light.h"



Light::Light()
{
	color = glm::vec3(1.0f, 1.0f, 1.0f);
	ambientIntensity = 1.0f;

	direction = glm::vec3(0.0f, -1.0f, 1.0f);
	diffuseIntensity = 0.0f;
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat intensity,
	GLfloat xdir, GLfloat ydir, GLfloat zdir, GLfloat dIntensity)
{
	color = glm::vec3(red, green, blue);
	ambientIntensity = intensity;

	direction = glm::vec3(xdir, ydir, zdir);
	diffuseIntensity = dIntensity;
}

void Light::UseLight(GLfloat ambientIntensityLoc, GLfloat ambientColorLoc,
	GLfloat diffuseIntensityLoc, GLfloat directionLoc)
{
	glUniform3f(ambientColorLoc, color.x, color.y, color.z);
	glUniform1f(ambientIntensityLoc, ambientIntensity);

	glUniform3f(directionLoc, direction.x, direction.y, direction.z);
	glUniform1f(diffuseIntensityLoc, diffuseIntensity);
}


Light::~Light()
{
}
