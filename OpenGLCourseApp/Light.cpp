#include "Light.h"



/*Light::Light()
{

}*/

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat intensity)
{
	color = glm::vec3(red, green, blue);
	ambientIntensity = intensity;
}

void Light::UseLight(GLfloat ambientIntensityLoc, GLfloat ambientColorLoc)
{
	glUniform3f(ambientColorLoc, color.x, color.y, color.z);
	glUniform1f(ambientIntensityLoc, ambientIntensity);
}


Light::~Light()
{
}
