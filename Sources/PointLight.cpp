#include "PointLight.h"

PointLight::PointLight() :Light()
{
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	coefficient = linear = 0.0f;
	constant = 1.0f;
}

PointLight::PointLight(GLuint shadowWidth, GLuint shadowHeight,
	GLfloat near, GLfloat far,
	GLfloat red, GLfloat green, GLfloat blue,
	GLfloat intensity, GLfloat dIntensity,
	GLfloat xPos, GLfloat yPos, GLfloat zPos,
	GLfloat con, GLfloat lin, GLfloat coef) :Light(shadowWidth, shadowHeight, red, green, blue, intensity, dIntensity)
{
	position = glm::vec3(xPos, yPos, zPos);
	coefficient = coef;
	linear = lin;
	constant = con;

	farPlane = far;
	float aspect = (float)shadowWidth / (float)shadowHeight;
	lightProj = glm::perspective(glm::radians(90.0f), aspect, near, far);

	shadowMap = new OmniShadowMap();
	shadowMap->Init(shadowWidth, shadowHeight);
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

std::vector<glm::mat4> PointLight::CalculateLightTransform()
{
	std::vector<glm::mat4> lightMatrices;

	//+x, -x
	lightMatrices.push_back(lightProj*glm::lookAt(position, position + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	lightMatrices.push_back(lightProj*glm::lookAt(position, position + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));

	//+y, -y
	lightMatrices.push_back(lightProj*glm::lookAt(position, position + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
	lightMatrices.push_back(lightProj*glm::lookAt(position, position + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
	
	//+z, -z
	lightMatrices.push_back(lightProj*glm::lookAt(position, position + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	lightMatrices.push_back(lightProj*glm::lookAt(position, position + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));

	return lightMatrices;
}

GLfloat PointLight::GetFarPlane()
{
	return farPlane;
}

glm::vec3 PointLight::GetPosition()
{
	return position;
}

PointLight::~PointLight()
{
}