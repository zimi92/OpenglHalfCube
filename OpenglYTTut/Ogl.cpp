#include "Ogl.h"
#include <sstream>
Ogl::Ogl()
{
	frameCount = 0;
	rotation = 0;
	previousTime = std::chrono::high_resolution_clock::now();
}


Ogl::~Ogl()
{
}

void Ogl::viewBasic() {
	ProgramID = Shaders::getProgramID();
	GLuint PositionID;
	GLuint ColorID;
	GLuint texCoord;
	GLuint normalID;
	PositionID = glGetAttribLocation(ProgramID, "position");
	ColorID = glGetAttribLocation(ProgramID, "colorDst");
	texCoord = glGetAttribLocation(ProgramID, "texCoord");
	normalID = glGetAttribLocation(ProgramID, "normal");
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	loadModel();

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	if(!numbers.empty())
		glBufferData(GL_ARRAY_BUFFER, numbers.size() * sizeof(Vertex), &numbers[0], GL_STATIC_DRAW);
	else
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
	lightPosID = glGetUniformLocation(ProgramID, "lightPos");
	GLuint modelID = glGetUniformLocation(ProgramID, "modelID");
	glm::mat4 projectionMatrix = glm::perspective(120.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	glm::mat4 View = glm::lookAt(
		glm::vec3(-3.0f, 3.0f, 4.0f),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
	);
	lightPos = glm::vec3(1.0f, 3.0f, 4.0f);
	float temp;
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(PositionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(ColorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(temp)));//(sizeof(vec3)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(texCoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(7 * sizeof(temp)));//(sizeof(vec3) + sizeof(vec4)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(normalID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(9 * sizeof(temp)));//(sizeof(vec3) + sizeof(vec4) + sizeof(vec2)));
	glBindVertexArray(VertexArrayID);

	glBindTexture(GL_TEXTURE_2D, texture);
	transform = glm::rotate(transform, 25.0f, glm::vec3(0.0, 1.0f, 0.0f));
	glUniformMatrix4fv(transfID, 1, GL_FALSE, glm::value_ptr(projectionMatrix * View));
	glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(transform));
	glUniform3f(lightPosID, lightPos.r, lightPos.g, lightPos.b);// glm::value_ptr(lightPos));

	glClearColor(0.1f, 0.0f, 0.0f, 1.0f);
}

void Ogl::loadModel() {
	std::string line;
	std::cout << "start" << std::endl;
	std::ifstream myStream("model2.txt");
	if (myStream.is_open()) {
		while (std::getline(myStream, line)) {
			std::istringstream iss(line);
			std::string token;
			while (std::getline(iss, token, ','))
			{
				numbers.push_back(atof(token.c_str()));
			}
		}
		myStream.close();
		return;
	}

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
}

GLuint Ogl::fpsCounter() {
	GLfloat fps = 0;
	frameCount++;
	currentTime = std::chrono::high_resolution_clock::now();
	std::chrono::milliseconds deltatime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - previousTime);
	if (deltatime.count() > 1000.0f) {
		fps = (float)frameCount / (deltatime.count() / 1000.0f);
		std::cout << fps << std::endl;
		previousTime = currentTime;
		frameCount = 0;
	}
	return (GLuint)fps;
}

void Ogl::draw(int vertices) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, vertices);
}

void Ogl::rotateLight(float speedOfLight) {
	std::chrono::milliseconds deltatime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - previousTime);
	if (deltatime.count() % 100 == 0) {
		lightPos = glm::vec3(4 * glm::sin(rotation += speedOfLight), 3.0f, 4 * glm::cos(rotation += speedOfLight));
		glUniform3f(lightPosID, lightPos.r, lightPos.g, lightPos.b);
	}
}

void Ogl::rotateModel(int axis, float angle) {
	GLuint modelID = glGetUniformLocation(ProgramID, "modelID");
	std::chrono::milliseconds deltatime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - previousTime);
	if (deltatime.count() % 100 == 0) {
		switch (axis)
		{
		case 0:
			transform = glm::rotate(transform, angle, glm::vec3(1.0, 0.0f, 0.0f));
		case 1:
			transform = glm::rotate(transform, angle, glm::vec3(0.0, 1.0f, 0.0f));
		case 2:
			transform = glm::rotate(transform, angle, glm::vec3(0.0, 0.0f, 1.0f));
		default:
			break;
		}
	}
	glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(transform));
}