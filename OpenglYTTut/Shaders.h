#pragma once
#include <GL\glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

class Shaders
{
public:
	Shaders();
	~Shaders();
	GLuint getProgramID();
private:
	GLuint m_ProgramID;
	const char* vert =
		"#version 330 core\n"
		"layout (location = 0) in vec3 position;"
		"layout (location = 1) in vec4 colorDst;"
		"layout (location = 2) in vec2 texCoord;"
		"layout (location = 3) in vec3 normal;"
		"uniform mat4 transform;"
		"uniform mat4 modelID;"
		"out vec2 texOut;"
		"out vec4 colorOut;"
		"out vec3 Normal;"
		"out vec3 FragPos;"
		"void main(){"
		"texOut = texCoord;"
		"colorOut = colorDst;"
		"gl_Position = transform * modelID * vec4(position, 1.0);"
		"Normal = mat3(transpose(inverse(modelID))) * normal;"
		"FragPos = vec3(modelID * vec4(position, 1.0));"
		"}";

	const char* frag =
		"#version 330 core\n"
		"out vec4 color;"
		"in vec2 texOut;"
		"in vec4 colorOut;"
		"in vec3 Normal;"
		"in vec3 FragPos;"
		"uniform vec3 lightPos;"
		"uniform sampler2D ourTexture;"
		"void main(){"
		"	vec3 norm = normalize(Normal);"
		"	vec3 lightDir = normalize(lightPos - FragPos);"
		"   float diff = max(dot(norm, lightDir), 0.0f);"
		"   vec3 diffuse = diff * vec3(1.0f, 1.0f, 1.0f);"
		"   vec3 ambient = vec3(0.4f, 0.4f, 0.4f);"
		"   vec3 result = (ambient + diffuse) * vec3(colorOut);"
		"	color = vec4(result, 1.0f);"
		"}";

};

