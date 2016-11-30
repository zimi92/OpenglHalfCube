#include <iostream>
#include <SDL2\SDL.h>
#undef main
#include <GL\glew.h>

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
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, .0f,
	};

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	
	glClearColor(1.0f, 0.5f, 0.3f, 1.0f);
	
	while (!is_Close) {
		SDL_GL_SwapWindow(m_window);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);
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