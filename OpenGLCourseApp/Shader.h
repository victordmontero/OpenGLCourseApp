#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL\glew.h>

#include <glm\gtc\type_ptr.hpp>

#include "CommonDefs.h"

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

class Shader
{
public:
	Shader();

	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);
	void CreateFromFiles(const char* vertexLocation, const char* geometryLocation, const char* fragmentLocation);

	void Validate();

	std::string ReadFile(const char* fileLocation);

	GLuint GetProjectionLocation();
	GLuint GetModelLocation();
	GLuint GetViewLocation();
	GLuint GetAmbientIntensityLocation();
	GLuint GetAmbientColorLocation();
	GLuint GetDiffuseIntensityLocation();
	GLuint GetDirectionLocation();
	GLuint GetSpecularIntensityLocation();
	GLuint GetShininessLocation();
	GLuint GetEyePositionLocation();
	GLuint GetOmniLightPosLocation();
	GLuint GetFarPlaneLocation();


	void SetDirectionalLight(DirectionalLight* light);
	void SetPointLights(PointLight* light, unsigned int lightCount, unsigned int textureUnit, unsigned int offset);
	void SetSpotLights(SpotLight* light, unsigned int lightCount, unsigned int textureUnit, unsigned int offset);
	void SetTexture(GLuint textureUnit);
	void SetDirectionalShadowMap(GLuint textureUnit);
	void SetDirectionalLightTransform(glm::mat4* transform);
	void SetLightMatrices(std::vector<glm::mat4> lightMatrices);

	void UseShader();
	void ClearShader();

	~Shader();

private:
	unsigned int pointLightCount;
	unsigned int spotLightCount;
	GLuint shaderID, uniformProjection, uniformModel, uniformView, uniformEyePosition,
		uniformSpecularIntensity, uniformShininess,
		uniformTexture,
		uniformDirectionalLightTransform, uniformDirectionalShadowMap,
		uniformOmniLightPos, uniformFarPlane;

	GLuint uniformLightMatrices[6];

	GLuint uniformPointLightCount;
	GLuint uniformSpotLightCount;
	struct {
		GLuint color;
		GLuint ambientIntensity;
		GLuint diffuseIntensity;

		GLuint direction;
	}uniformDirectionalLight;

	struct {
		GLuint color;
		GLuint ambientIntensity;
		GLuint diffuseIntensity;

		GLuint position;
		GLuint coefficient;
		GLuint linear;
		GLuint constant;
	}uniformPointLight[MAX_POINT_LIGHTS];

	struct {
		GLuint color;
		GLuint ambientIntensity;
		GLuint diffuseIntensity;

		GLuint position;
		GLuint coefficient;
		GLuint linear;
		GLuint constant;

		GLuint direction;
		GLuint edge;
	}uniformSpotLight[MAX_SPOT_LIGHTS];

	struct {
		GLuint shadowMap;
		GLuint farPlane;
	} uniformOmniShadowMap[MAX_POINT_LIGHTS + MAX_SPOT_LIGHTS];

	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void CompileShader(const char* vertexCode, const char* geometryCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);

	void CompileProgram();
};
