#include <iostream>
#include <vector>
#include <SDL2\SDL.h>
#include <SOIL.h>
#undef main
#include <GL\glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Ogl.h"

int main() {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_Window *m_window = SDL_CreateWindow("window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 200, 200, SDL_WINDOW_OPENGL);
	SDL_GLContext m_GLcontext = SDL_GL_CreateContext(m_window);

	Ogl oglMain;
	oglMain.viewBasic();
	
	SDL_Event e;
	bool is_Close = false;
	float rotation = 0;
	float lightSpeed = 0.01;
	float rotateSpeed = 0.01;
	int rotateDirection = 0;
	while (!is_Close) {
		SDL_GL_SwapWindow(m_window);
		oglMain.draw(18);
		oglMain.fpsCounter();
		oglMain.rotateLight(lightSpeed);
		oglMain.rotateModel(rotateDirection, rotateSpeed);

		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				is_Close = true;
			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_a: {
					lightSpeed += 0.01;
					break;
				}
				case SDLK_d: {
					lightSpeed -= 0.01;
					break;
				}
				case SDLK_i: {
					rotateDirection = 1;
					break;
				}
				case SDLK_j: {
					rotateDirection = 2;
					break;
				}
				case SDLK_y: {
					rotateDirection = 0;
					break;
				}
				default:
					break;
				}
			}			
		}
	}
	SDL_GL_DeleteContext(m_GLcontext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
	return 0;
}