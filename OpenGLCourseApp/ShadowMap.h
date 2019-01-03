#pragma once

#include <cstdio>
#include <GL/glew.h>

class ShadowMap
{
public:
	ShadowMap();
	
	virtual bool Init(unsigned int width, unsigned int height);
	virtual void Write();
	virtual void Read(GLenum textureUnit);

	GLuint GetShadowWidth() { return shadowWidth; }
	GLuint GetShadowHeight() { return shadowHeight; }

	~ShadowMap();

protected:
	GLuint FBO, shadowMap;
	GLuint shadowWidth, shadowHeight;
};

