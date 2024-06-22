#pragma once

extern "C"
{
#include <glad/gl.h>
}

class Material
{
public:
	Material();
	Material(GLfloat sIntensity, GLfloat shine);

	void UseMaterial(GLuint specularIntensityLoc, GLuint shininessLoc);

	~Material();

private:
	GLfloat specularIntensity;
	GLfloat shininess;
};

