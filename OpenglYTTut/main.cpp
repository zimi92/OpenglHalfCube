#include <iostream>
#include <vector>
#include <SDL2\SDL.h>
#include <SOIL.h>
#undef main
#include <GL\glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

	SDL_Event e;
	bool is_Close = false;
	//OPENGL PART
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		printf("glew doesn't work");
		return -1;
	}
	
	while (!is_Close) {
		SDL_GL_SwapWindow(m_window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 18);
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				is_Close = true;
		}
	}
	SDL_GL_DeleteContext(m_GLcontext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
	return 0;
}