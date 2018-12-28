#pragma once

#include<cstring>
#include <GL/glew.h>
#include "stb_image.h"

class Texture
{
public:
	Texture();
	Texture(char* fileLoc);
	~Texture();

	void LoadTexture();
	void UseTexture();
	void ClearTexture();

private:
	GLuint textureId;
	int width, height, bitDepth;
	char* fileLocation;
};

