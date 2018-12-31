#include "PointLight.h"

PointLight::PointLight() :Light()
{
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	coefficient = linear = 0.0f;
	constant = 1.0f;
}

PointLight::PointLight(GLfloat red, GLfloat green, GLfloat blue,
	GLfloat intensity, GLfloat dIntensity,
	GLfloat xPos, GLfloat yPos, GLfloat zPos,
	GLfloat con, GLfloat lin, GLfloat coef) :Light(red, green, blue, intensity, dIntensity)
{
	position = glm::vec3(xPos, yPos, zPos);
	coefficient = coef;
	linear = lin;
	constant = con;
}

void PointLight::UseLight(GLuint ambientIntensityLoc, GLuint ambientColorLoc, GLuint diffuseIntensityLoc,
	GLuint positionLoc, GLuint constantLoc, GLuint linearLoc, GLuint coeffientLoc)
{
	Light::UseLight(ambientIntensityLoc, ambientColorLoc, diffuseIntensityLoc);
	glUniform3f(positionLoc, position.x, position.y, position.z);
	glUniform1f(coeffientLoc, coefficient);
	glUniform1f(linearLoc, linear);
	glUniform1f(constantLoc, constant);
}


PointLight::~PointLight()
{
}