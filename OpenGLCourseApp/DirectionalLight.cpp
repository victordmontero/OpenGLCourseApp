#include "DirectionalLight.h"



DirectionalLight::DirectionalLight() : Light()
{
	direction = glm::vec3(0.0f, -1.0f, 1.0f);
}

DirectionalLight::DirectionalLight(GLfloat red, GLfloat green, GLfloat blue,
	GLfloat intensity, GLfloat dIntensity,
	GLfloat xdir, GLfloat ydir, GLfloat zdir) : Light(red, green, blue, intensity, dIntensity)
{
	direction = glm::vec3(xdir, ydir, zdir);
}

void DirectionalLight::UseLight(GLuint ambientIntensityLoc, GLuint ambientColorLoc,
	GLuint diffuseIntensityLoc, GLuint directionLoc)
{
	Light::UseLight(ambientIntensityLoc, ambientColorLoc, diffuseIntensityLoc);
	glUniform3f(directionLoc, direction.x, direction.y, direction.z);
}

Light::~Light()
{
}

DirectionalLight::~DirectionalLight()
{
}
