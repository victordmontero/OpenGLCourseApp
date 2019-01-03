#include "DirectionalLight.h"



DirectionalLight::DirectionalLight() : Light()
{
	direction = glm::vec3(0.0f, -1.0f, 0.0f);
}

DirectionalLight::DirectionalLight(GLuint shadowWidth, GLuint shadowHeight,
	GLfloat red, GLfloat green, GLfloat blue,
	GLfloat intensity, GLfloat dIntensity,
	GLfloat xdir, GLfloat ydir, GLfloat zdir) : Light(shadowWidth, shadowHeight, red, green, blue, intensity, dIntensity)
{
	direction = glm::vec3(xdir, ydir, zdir);
	lightProj = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 100.0f);
}

void DirectionalLight::UseLight(GLuint ambientIntensityLoc, GLuint ambientColorLoc,
	GLuint diffuseIntensityLoc, GLuint directionLoc)
{
	Light::UseLight(ambientIntensityLoc, ambientColorLoc, diffuseIntensityLoc);
	glUniform3f(directionLoc, direction.x, direction.y, direction.z);
}

glm::mat4 DirectionalLight::CalculateLightTransform()
{
	return lightProj * glm::lookAt(-direction, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

Light::~Light()
{
}

DirectionalLight::~DirectionalLight()
{
}
