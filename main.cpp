#include <iostream>
#include <cmath>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaderClass.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "texture.h"
#include "camera.h"

const unsigned int width{ 800 };
const unsigned int height{ 800 };

GLfloat vertices[]{
	// Front face
	-0.25f, -0.25f, -0.25f,  0.25f, 0.25f, 0.25f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f, // 0
	 0.25f, -0.25f, -0.25f,  0.25f, 0.25f, 0.25f,  1.0f, 0.0f,  0.0f, 0.0f, -1.0f, // 1
	 0.25f,  0.25f, -0.25f,  0.25f, 0.25f, 0.25f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f, // 2
	-0.25f,  0.25f, -0.25f,  0.25f, 0.25f, 0.25f,  0.0f, 1.0f,  0.0f, 0.0f, -1.0f, // 3

	// Back face
	-0.25f, -0.25f,  0.25f,  0.25f, 0.25f, 0.25f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f, // 4
	 0.25f, -0.25f,  0.25f,  0.25f, 0.25f, 0.25f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,// 5
	 0.25f,  0.25f,  0.25f,  0.25f, 0.25f, 0.25f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,// 6
	-0.25f,  0.25f,  0.25f,  0.25f, 0.25f, 0.25f,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f,// 7

	// Left face
	-0.25f, -0.25f, -0.25f,  0.25f, 0.25f, 0.25f,  0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,// 8
	-0.25f, -0.25f,  0.25f,  0.25f, 0.25f, 0.25f,  1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,// 9
	-0.25f,  0.25f,  0.25f,  0.25f, 0.25f, 0.25f,  1.0f, 1.0f,  -1.0f, 0.0f, 0.0f,// 10
	-0.25f,  0.25f, -0.25f,  0.25f, 0.25f, 0.25f,  0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,// 11

	// Right face
	 0.25f, -0.25f, -0.25f,  0.25f, 0.25f, 0.25f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,// 12
	 0.25f, -0.25f,  0.25f,  0.25f, 0.25f, 0.25f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,// 13
	 0.25f,  0.25f,  0.25f,  0.25f, 0.25f, 0.25f,  1.0f, 1.0f,  1.0f, 0.0f, 0.0f,// 14
	 0.25f,  0.25f, -0.25f,  0.25f, 0.25f, 0.25f,  0.0f, 1.0f,  1.0f, 0.0f, 0.0f,// 15

	 // Bottom face
	 -0.25f, -0.25f, -0.25f,  0.25f, 0.25f, 0.25f,  0.0f, 0.0f,  0.0f, -1.0f, 0.0f,// 16
	  0.25f, -0.25f, -0.25f,  0.25f, 0.25f, 0.25f,  1.0f, 0.0f,  0.0f, -1.0f, 0.0f,// 17
	  0.25f, -0.25f,  0.25f,  0.25f, 0.25f, 0.25f,  1.0f, 1.0f,  0.0f, -1.0f, 0.0f,// 18
	 -0.25f, -0.25f,  0.25f,  0.25f, 0.25f, 0.25f,  0.0f, 1.0f,  0.0f, -1.0f, 0.0f,// 19

	 // Top face
	 -0.25f,  0.25f, -0.25f,  0.25f, 0.25f, 0.25f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f,// 20
	  0.25f,  0.25f, -0.25f,  0.25f, 0.25f, 0.25f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,// 21
	  0.25f,  0.25f,  0.25f,  0.25f, 0.25f, 0.25f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f,// 22
	 -0.25f,  0.25f,  0.25f,  0.25f, 0.25f, 0.5f,	0.0f, 1.0f,  0.0f, 1.0f, 0.0f,// 23
};	  //3x coord,		   3x color,		  2x textcoord		3x normals

GLuint indices[]{
	// Front
	0, 1, 2,  0, 2, 3,
	// Back
	4, 5, 6,  4, 6, 7,
	// Left
	8, 9, 10, 8, 10, 11,
	// Right
	12, 13, 14, 12, 14, 15,
	// Bottom
	16, 17, 18, 16, 18, 19,
	// Top
	20, 21, 22, 20, 22, 23
};

GLfloat cuboidVertices[]{
	// Front face
	-0.25f, -0.25f, -0.25f,
	 0.25f, -0.25f, -0.25f,
	 0.25f,  0.25f, -0.25f,
	-0.25f,  0.25f, -0.25f,

	// Back face
	-0.25f, -0.25f,  0.25f,
	 0.25f, -0.25f,  0.25f,
	 0.25f,  0.25f,  0.25f,
	-0.25f,  0.25f,  0.25f,

	// Left face
	-0.25f, -0.25f, -0.25f,
	-0.25f, -0.25f,  0.25f,
	-0.25f,  0.25f,  0.25f,
	-0.25f,  0.25f, -0.25f,

	// Right face
	 0.25f, -0.25f, -0.25f,
	 0.25f, -0.25f,  0.25f,
	 0.25f,  0.25f,  0.25f,
	 0.25f,  0.25f, -0.25f,

	 // Bottom face
	 -0.25f, -0.25f, -0.25f,
	  0.25f, -0.25f, -0.25f,
	  0.25f, -0.25f,  0.25f,
	 -0.25f, -0.25f,  0.25f,

	 // Top face
	 -0.25f,  0.25f, -0.25f,
	  0.25f,  0.25f, -0.25f,
	  0.25f,  0.25f,  0.25f,
	 -0.25f,  0.25f,  0.25f,
};	  //3x coord,		   3x color,		  2x textcoord		3x normals

GLuint cuboidIndices[]{
	// Front
	0, 1, 2,  0, 2, 3,
	// Back
	4, 5, 6,  4, 6, 7,
	// Left
	8, 9, 10, 8, 10, 11,
	// Right
	12, 13, 14, 12, 14, 15,
	// Bottom
	16, 17, 18, 16, 18, 19,
	// Top
	20, 21, 22, 20, 22, 23
};

GLfloat mirrorVertices[] =
{
	-0.5f,	-0.5f,	0.0f,
	0.5f,	-0.5f,	0.0f,
	0.5f,	0.5f,	0.0f,
	-0.5f,	0.5f,	0.0f
};

GLuint mirrorIndices[] =
{
	0, 1, 2,
	0, 2, 3
};

GLfloat planeVertices[] =
{ //     COORDINATES x3    // color x3 tex x2 normals x3
	-1.0f,	0.0f,	-1.0f,	0.5f,	0.5f,	0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,
	1.0f,	0.0f,	-1.0f,	0.5f,	0.5f,	0.5f,	5.0f,	0.0f,	0.0f,	1.0f,	0.0f,
	1.0f,	0.0f,	1.0f,	0.5f,	0.5f,	0.5f,	5.0f,	5.0f,	0.0f,	1.0f,	0.0f,
	-1.0f,	0.0f,	1.0f,	0.5f,	0.5f,	0.5f,	0.0f,	5.0f,	0.0f,	1.0f,	0.0f
};

GLuint planeIndices[] =
{
	0, 1, 2,
	0, 2, 3
};

std::vector<GLfloat> generateSphereVertices(float radius, int sectors, int stacks) {
	std::vector<GLfloat> vertices;
	const float PI = acos(-1.0f);

	for (int i = 0; i <= stacks; ++i) {
		float stackAngle = PI / 2 - i * (PI / stacks);
		float xy = radius * cosf(stackAngle);
		float z = radius * sinf(stackAngle);

		for (int j = 0; j <= sectors; ++j) {
			float sectorAngle = j * (2 * PI / sectors);
			float x = xy * cosf(sectorAngle);
			float y = xy * sinf(sectorAngle);
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);
			vertices.push_back(x / radius);
			vertices.push_back(y / radius);
			vertices.push_back(z / radius);
		}
	}
	return vertices;
}

std::vector<GLuint> generateSphereIndices(int sectors, int stacks) {
	std::vector<GLuint> indices;
	for (int i = 0; i < stacks; ++i) {
		int k1 = i * (sectors + 1);
		int k2 = k1 + sectors + 1;

		for (int j = 0; j < sectors; ++j, ++k1, ++k2) {
			if (i != 0) {
				indices.push_back(k1);
				indices.push_back(k2);
				indices.push_back(k1 + 1);
			}
			if (i != (stacks - 1)) {
				indices.push_back(k1 + 1);
				indices.push_back(k2);
				indices.push_back(k2 + 1);
			}
		}
	}
	return indices;
}

glm::mat4 createCuboidModel(glm::vec3 position, glm::vec3 scale, float rotationAngle = 0.0f, glm::vec3 rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f)) {
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = glm::rotate(model, glm::radians(rotationAngle), rotationAxis);
	model = glm::scale(model, scale);
	return model;
}

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "okno", NULL, NULL);
	if (window == NULL) {
		std::cout << "Okno nie dziala!";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();
	glViewport(0, 0, width, height);

	Shader shaderProgram("default.vert", "default.frag");
	Shader lightShader("light.vert", "light.frag");
	Shader mirrorShader("mirror.vert", "mirror.frag");
	Shader planeShader("plane.vert", "plane.frag");
	
	VAO VAO1;
	VAO1.Bind();
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));
	VAO1.LinkAttributes(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO1.LinkAttributes(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttributes(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.LinkAttributes(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	const float sphereRadius = 0.1f;
	const int sectors = 36;
	const int stacks = 18;
	std::vector<GLfloat> sphereVertices = generateSphereVertices(sphereRadius, sectors, stacks);
	std::vector<GLuint> sphereIndices = generateSphereIndices(sectors, stacks);

	VAO lightVAO;
	lightVAO.Bind();
	VBO lightVBO(sphereVertices.data(), sphereVertices.size() * sizeof(GLfloat));
	EBO lightEBO(sphereIndices.data(), sphereIndices.size() * sizeof(GLuint));
	lightVAO.LinkAttributes(lightVBO, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	lightVAO.LinkAttributes(lightVBO, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();

	VAO mirrorVAO;
	mirrorVAO.Bind();
	VBO mirrorVBO(mirrorVertices, sizeof(mirrorVertices));
	EBO mirrorEBO(mirrorIndices, sizeof(mirrorIndices));
	mirrorVAO.LinkAttributes(mirrorVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	mirrorVAO.Unbind();
	mirrorVBO.Unbind();
	mirrorEBO.Unbind();

	VAO planeVAO;
	planeVAO.Bind();
	VBO planeVBO(planeVertices, sizeof(planeVertices));
	EBO planeEBO(planeIndices, sizeof(planeIndices));
	planeVAO.LinkAttributes(planeVBO, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	planeVAO.LinkAttributes(planeVBO, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	planeVAO.LinkAttributes(planeVBO, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	planeVAO.LinkAttributes(planeVBO, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	planeVAO.Unbind();
	planeVBO.Unbind();
	planeEBO.Unbind();

	VAO cuboidVAO;
	cuboidVAO.Bind();
	VBO cuboidVBO(vertices, sizeof(vertices));
	EBO cuboidEBO(cuboidIndices, sizeof(cuboidIndices));
	cuboidVAO.LinkAttributes(cuboidVBO, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	cuboidVAO.LinkAttributes(cuboidVBO, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	cuboidVAO.LinkAttributes(cuboidVBO, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	cuboidVAO.LinkAttributes(cuboidVBO, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	cuboidVAO.Unbind();
	cuboidVBO.Unbind();
	cuboidEBO.Unbind();


	glm::mat4 reflectionMatrix = glm::mat4(
		-1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		4.0f, 0.0f, 0.0f, 1.0f
	);

	Texture popCat("pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	popCat.texUnit(shaderProgram, "tex0", 0);
	Texture grass("grass.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	grass.texUnit(planeShader, "tex0", 0);
	Texture torsoTex("torso.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	torsoTex.texUnit(shaderProgram, "tex0", 0);

	Camera camera(width, height, glm::vec3(0.9f, 0.1f, 3.0f));

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);

	float radius = 1.0f;
	glm::vec3 cubePos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 cubeModel = glm::mat4(1.0f);
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(cubeModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

	glm::vec3 startPos(0.2f, 0.6f, 0.0f);
	glm::vec3 mirrorPos(1.9f, 0.5f, 0.0f);
	glm::vec3 groundPos(1.0f, -0.4f, 0.0f);

	glm::vec3 control1(1.0f, 1.5f, 0.0f);
	glm::vec3 control2(1.5f, 0.5f, 0.0f);
	glm::vec3 control3(0.5f, 1.0f, 0.0f);

	float totalDuration = 6.0f;
	
	glm::vec3 basePosition(0.0f, 0.0f, 0.0f);
	while (!glfwWindowShouldClose(window)) {
		glViewport(0, 0, width, height);
		glClearColor(0.53f, 0.8f, 0.92f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		camera.Inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		// Obliczanie pozycji swiatla
		float time = glfwGetTime();
		float cycleTime = fmod(time, totalDuration);
		float segmentTime = fmod(cycleTime, 2.0f) / 2.0f;
		glm::vec3 lightPos;
		int segment = static_cast<int>(cycleTime / 2.0f);

		switch (segment) {
		case 0: // startPos -> mirrorPos
			lightPos = (1 - segmentTime) * (1 - segmentTime) * startPos +
				2 * (1 - segmentTime) * segmentTime * control1 +
				segmentTime * segmentTime * mirrorPos;
			break;
		case 1: // mirrorPos -> groundPos
			lightPos = (1 - segmentTime) * (1 - segmentTime) * mirrorPos +
				2 * (1 - segmentTime) * segmentTime * control2 +
				segmentTime * segmentTime * groundPos;
			break;
		case 2: // groundPos -> startPos
			lightPos = (1 - segmentTime) * (1 - segmentTime) * groundPos +
				2 * (1 - segmentTime) * segmentTime * control3 +
				segmentTime * segmentTime * startPos;
			break;
		}

		// tulow
		shaderProgram.Activate();
		glm::mat4 torsoModel = createCuboidModel(
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.6f, 2.0f, 1.0f)
		);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(torsoModel));
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		camera.Matrix(shaderProgram, "camMatrix");
		cuboidVAO.Bind();
		torsoTex.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(cuboidIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

		// glowa
		glm::mat4 headModel = glm::mat4(1.0f);
		headModel = glm::translate(headModel, glm::vec3(0.0f, 0.65f, 0.0f));
		headModel = glm::scale(headModel, glm::vec3(0.8f, 0.8f, 0.8f));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(headModel));
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		camera.Matrix(shaderProgram, "camMatrix");
		popCat.Bind();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		// plaszczyzna
		planeShader.Activate();
		glm::mat4 planeModel = glm::mat4(1.0f);
		planeModel = glm::translate(planeModel, glm::vec3(0.0f, -0.5f, 0.0f));
		planeModel = glm::scale(planeModel, glm::vec3(5.0f, 1.0f, 5.0f));
		glUniformMatrix4fv(glGetUniformLocation(planeShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(planeModel));
		glUniform3f(glGetUniformLocation(planeShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform4f(glGetUniformLocation(planeShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		camera.Matrix(planeShader, "camMatrix");
		grass.Bind();
		planeVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(planeIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		// sfera
		lightShader.Activate();
		glm::mat4 lightModel = glm::mat4(1.0f);
		lightModel = glm::translate(lightModel, lightPos);
		glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
		glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		camera.Matrix(lightShader, "camMatrix");
		lightVAO.Bind();
		glDrawElements(GL_TRIANGLES, sphereIndices.size(), GL_UNSIGNED_INT, 0);

		glEnable(GL_STENCIL_TEST);
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glStencilMask(0xFF);
		glDepthMask(GL_FALSE);
		glClear(GL_STENCIL_BUFFER_BIT);

		// lustro
		mirrorShader.Activate();
		glm::mat4 mirrorModel = glm::mat4(1.0f);
		mirrorModel = glm::rotate(mirrorModel, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		mirrorModel = glm::translate(mirrorModel, glm::vec3(0.0f, 0.0f, 2.0f));
		mirrorModel = glm::scale(mirrorModel, glm::vec3(1.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(glGetUniformLocation(mirrorShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(mirrorModel));
		camera.Matrix(mirrorShader, "camMatrix");
		mirrorVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(mirrorIndices) / sizeof(int), GL_UNSIGNED_INT, 0);


		glStencilFunc(GL_EQUAL, 1, 0xFF);
		glStencilMask(0x00);
		glDepthMask(GL_TRUE);

		// odbicie plaszczyzny
		planeShader.Activate();
		planeModel = glm::translate(planeModel, glm::vec3(0.0f, 0.1f, 0.0f));
		planeModel = glm::scale(planeModel, glm::vec3(3.0f, 1.0f, 3.0f));
		glUniformMatrix4fv(glGetUniformLocation(planeShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(planeModel));
		glUniform3f(glGetUniformLocation(planeShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform4f(glGetUniformLocation(planeShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		camera.Matrix(planeShader, "camMatrix");
		grass.Bind();
		planeVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(planeIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		// Odbicie tulowia
		shaderProgram.Activate();
		glm::mat4 reflectedTorsoModel = reflectionMatrix * torsoModel;
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(reflectedTorsoModel));
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgram, "camMatrix");
		torsoTex.Bind();
		cuboidVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(cuboidIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

		// Odbicie glowy
		glm::mat4 reflectedHeadModel = reflectionMatrix * headModel;
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(reflectedHeadModel));
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgram, "camMatrix");
		popCat.Bind();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		// Odbicie sfery
		lightShader.Activate();
		glm::mat4 reflectedLightModel = reflectionMatrix * lightModel;
		glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(reflectedLightModel));
		glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		camera.Matrix(lightShader, "camMatrix");
		lightVAO.Bind();
		glDrawElements(GL_TRIANGLES, sphereIndices.size(), GL_UNSIGNED_INT, 0);

		glDisable(GL_STENCIL_TEST);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	popCat.Delete();
    grass.Delete();
    torsoTex.Delete();
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    cuboidVAO.Delete();
    cuboidVBO.Delete();
    cuboidEBO.Delete();
    lightVAO.Delete();
    lightVBO.Delete();
    lightEBO.Delete();
    mirrorVAO.Delete();
    mirrorVBO.Delete();
    mirrorEBO.Delete();
    planeVAO.Delete();
    planeVBO.Delete();
    planeEBO.Delete();
    shaderProgram.Delete();
    lightShader.Delete();
    mirrorShader.Delete();
    planeShader.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}