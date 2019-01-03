#include "Light.h"



Light::Light()
{
	color = glm::vec3(1.0f, 1.0f, 1.0f);
	ambientIntensity = 1.0f;
	diffuseIntensity = 0.0f;
}

Light::Light(GLuint shadowWidth, GLuint shadowHeight, GLfloat red, GLfloat green, GLfloat blue, GLfloat intensity, GLfloat dIntensity)
{

	color = glm::vec3(red, green, blue);
	ambientIntensity = intensity;
	diffuseIntensity = dIntensity;

	shadowMap = new ShadowMap();
	shadowMap->Init(shadowWidth, shadowHeight);
}

void Light::UseLight(GLuint ambientIntensityLoc, GLuint ambientColorLoc, GLuint diffuseIntensityLoc)
{
	glUniform3f(ambientColorLoc, color.x, color.y, color.z);
	glUniform1f(ambientIntensityLoc, ambientIntensity);
	glUniform1f(diffuseIntensityLoc, diffuseIntensity);
}


//Light::~Light()
//{
//}
