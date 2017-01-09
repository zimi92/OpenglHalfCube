#include "Shaders.h"



Shaders::Shaders()
{
	//OPENGL PART
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		printf("glew doesn't work");
	}

	GLuint ProgramID = glCreateProgram();
	GLuint vID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fID = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vID, 1, &vert, NULL);
	glShaderSource(fID, 1, &frag, NULL);

	glCompileShader(vID);
	glCompileShader(fID);

	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	glGetShaderiv(fID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glAttachShader(ProgramID, vID);
	glAttachShader(ProgramID, fID);

	glLinkProgram(ProgramID);
	glUseProgram(ProgramID);
	m_ProgramID = ProgramID;
}

GLuint Shaders::getProgramID() {
	return m_ProgramID;
}

Shaders::~Shaders()
{
}
