#pragma once
#include "PointLight.h"
class SpotLight :
	public PointLight
{
public:
	SpotLight();
	SpotLight(GLfloat red, GLfloat green, GLfloat blue,
		GLfloat intensity, GLfloat dIntensity,
		GLfloat xPos, GLfloat yPos, GLfloat zPos,
		GLfloat xDir, GLfloat yDir, GLfloat zDir,
		GLfloat con, GLfloat lin, GLfloat exp,
		GLfloat edg);

	virtual void UseLight(GLuint ambientIntensityLoc, GLuint ambientColorLoc,
		GLuint diffuseIntensityLoc, GLuint positionLoc, GLfloat directionLoc,
		GLuint constantLoc, GLuint linearLoc, GLuint coeffientLoc, GLuint edgeLoc);

	void SetFlash(glm::vec3 pos, glm::vec3 dir);

	~SpotLight();

private:
	glm::vec3 direction;

	GLfloat edge, procEdge;
};

