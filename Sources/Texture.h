#pragma once

#include<cstring>
#include <GL/glew.h>
#include "CommonDefs.h"

class Texture
{
public:
	Texture();
	Texture(const char* fileLoc);
	~Texture();

	bool LoadTexture();
	bool LoadTextureA();
	void UseTexture();
	void ClearTexture();

private:
	GLuint textureId;
	int width, height, bitDepth;
	const char* fileLocation;
};

