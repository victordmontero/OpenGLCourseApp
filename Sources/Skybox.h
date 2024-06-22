#pragma once

#include <vector>
#include <string>

extern "C"
{
#include <glad/gl.h>
}

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "CommonDefs.h"

#include "Shader.h"
#include "Mesh.h"

class Skybox
{
public:
	Skybox();

	Skybox(std::vector<std::string> faceLocations);

	void DrawSkyBox(glm::mat4 view, glm::mat4 projection);

	~Skybox();
private:
	Mesh* skyMesh;
	Shader* skyShader;

	GLuint textureId;
	GLuint uniformProjection, uniformView;
};

