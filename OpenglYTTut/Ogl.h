#pragma once
#include "Shaders.h"
#include <iostream>
#include <vector>
#include <SDL2\SDL.h>
#include <SOIL.h>
#include <fstream>
#include <string>
class Ogl: public Shaders
{
public:
	//glm::vec3 lightPos;
	//GLuint lightPosID;
	Ogl();
	~Ogl();
	void viewBasic();
	void draw();
	void loadModel();
};

