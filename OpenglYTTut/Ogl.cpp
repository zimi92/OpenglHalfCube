#include "Ogl.h"

Ogl::Ogl()
{
}


Ogl::~Ogl()
{
}

void Ogl::viewBasic() {
	GLuint ProgramID = Shaders::getProgramID();
	GLuint PositionID;
	GLuint ColorID;
	GLuint texCoord;
	GLuint normalID;
	PositionID = glGetAttribLocation(ProgramID, "position");
	ColorID = glGetAttribLocation(ProgramID, "colorDst");
	texCoord = glGetAttribLocation(ProgramID, "texCoord");
	normalID = glGetAttribLocation(ProgramID, "normal");
	std::cout << ColorID << std::endl;
	std::cout << PositionID << std::endl;
	std::cout << ProgramID << std::endl;
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	static const GLfloat g_color_buffer_data[] = {
		1.0f, 1.0f, 0.0f,
		1.0f
	};
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
	//front1
	Vertex v0 = { vec3(-1.0f, -1.0f, 1.0f),vec4(1.0f, 0.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f) };
	Vertex v1 = { vec3(-1.0f, 1.0f, 1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f), vec2(1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f) };
	Vertex v2 = { vec3(1.0f, 1.0f, 1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f), vec2(1.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f) };
	//front2
	Vertex v3 = { vec3(1.0f, 1.0f, 1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f), vec2(0.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f) };
	Vertex v4 = { vec3(1.0f, -1.0f, 1.0f),vec4(1.0f, 0.0f, 0.0f, 1.0f), vec2(1.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f) };
	Vertex v5 = { vec3(-1.0f, -1.0f, 1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f), vec2(1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f) };
	//left1
	Vertex v6 = { vec3(-1.0f, 1.0f, -1.0f),vec4(0.0f, 1.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f) };
	Vertex v7 = { vec3(-1.0f, -1.0f, -1.0f), vec4(0.0f, 1.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f) };
	Vertex v8 = { vec3(-1.0f, 1.0f, 1.0f), vec4(0.0f, 1.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f) };
	//left2
	Vertex v9 = { vec3(-1.0f, 1.0f, 1.0f), vec4(0.0f, 1.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f) };
	Vertex v10 = { vec3(-1.0f, -1.0f, 1.0f),vec4(0.0f, 1.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f) };
	Vertex v11 = { vec3(-1.0f, -1.0f, -1.0f), vec4(0.0f, 1.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f) };
	//top1
	Vertex v12 = { vec3(-1.0f, 1.0f, -1.0f),vec4(0.0f, 0.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f) };
	Vertex v13 = { vec3(1.0f, 1.0f, -1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f) };
	Vertex v14 = { vec3(1.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f) };
	//top2
	Vertex v15 = { vec3(1.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f) };
	Vertex v16 = { vec3(-1.0f, 1.0f, 1.0f),vec4(0.0f, 0.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f) };
	Vertex v17 = { vec3(-1.0f, 1.0f, -1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f) };

	triangle.push_back(v0);
	triangle.push_back(v1);
	triangle.push_back(v2);
	triangle.push_back(v3);
	triangle.push_back(v4);
	triangle.push_back(v5);
	triangle.push_back(v6);
	triangle.push_back(v7);
	triangle.push_back(v8);
	triangle.push_back(v9);
	triangle.push_back(v10);
	triangle.push_back(v11);
	triangle.push_back(v12);
	triangle.push_back(v13);
	triangle.push_back(v14);
	triangle.push_back(v15);
	triangle.push_back(v16);
	triangle.push_back(v17);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, triangle.size() * sizeof(Vertex), &triangle[0], GL_STATIC_DRAW);

	GLuint indexBuffer;

	int width, height;
	unsigned char* image = SOIL_load_image("tex1.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	//transformations

	GLuint transfID = glGetUniformLocation(ProgramID, "transform");
	GLuint lightPosID = glGetUniformLocation(ProgramID, "lightPos");
	GLuint modelID = glGetUniformLocation(ProgramID, "modelID");
	glm::mat4 projectionMatrix = glm::perspective(120.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	glm::mat4 View = glm::lookAt(
		glm::vec3(-3.0f, 3.0f, 4.0f),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
	);
	glm::vec3 lightPos = glm::vec3(1.0f, 3.0f, 4.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(PositionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(ColorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec3)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(texCoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec3) + sizeof(vec4)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(normalID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec3) + sizeof(vec4) + sizeof(vec2)));
	glBindVertexArray(VertexArrayID);

	glBindTexture(GL_TEXTURE_2D, texture);
	GLfloat rotation = 0.1;
	glm::mat4 transform;
	glUniformMatrix4fv(transfID, 1, GL_FALSE, glm::value_ptr(projectionMatrix * View));
	glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(transform));
	glUniform3f(lightPosID, lightPos.r, lightPos.g, lightPos.b);// glm::value_ptr(lightPos));

	glClearColor(0.1f, 0.0f, 0.0f, 1.0f);
}
