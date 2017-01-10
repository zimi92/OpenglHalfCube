#pragma once
#include "Shaders.h"
#include <iostream>
#include <vector>
#include <SDL2\SDL.h>
#include <SOIL.h>
#include <fstream>
#include <string>
#include <ctime>
#include <chrono>
class Ogl: public Shaders
{
	std::vector <float> numbers;
	struct vec2 {
		vec2(float _r = 1, float _g = 1) :r(_r), g(_g) {}
		float r, g;
	};
	struct vec3 {
		vec3(float _r = 1, float _g = 1, float _b = 1) :r(_r), g(_g), b(_b) {}
		float r, g, b;
	};
	struct vec4 {
		vec4(float _r = 1, float _g = 1, float _b = 1, float _a = 1) :r(_r), g(_g), b(_b), a(_a) {}
		float r, g, b, a;
	};
	struct Vertex {
		vec3 position;
		vec4 color;
		vec2 texture;
		vec3 normal;
	};

	std::vector<Vertex> triangle;
	GLuint frameCount;
	std::chrono::steady_clock::time_point  currentTime;
	std::chrono::steady_clock::time_point previousTime;
public:
	//glm::vec3 lightPos;
	//GLuint lightPosID;
	Ogl();
	~Ogl();
	void viewBasic();
	void draw();
	void loadModel();
	GLuint fpsCounter();
};

