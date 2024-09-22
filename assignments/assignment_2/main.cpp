#include <stdio.h>
#include <math.h>

#include <ew/external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <shader.h>



const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

float vertices[] = {
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
};

int main() {
	// Initialization of program --- 
	printf("Initializing...");
	if (!glfwInit()) {
		printf("GLFW failed to init!");
		return 1;
	}
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Assignment 2 Thing", NULL, NULL);
	if (window == NULL) {
		printf("GLFW failed to create window");
		return 1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGL(glfwGetProcAddress)) {
		printf("GLAD Failed to load GL headers");
		return 1;
	}
	// end of window section ---
	
	Shader ourShader("Vertexshader.vert","Fragmentshader.frag");

	//Initialization goes here!
	unsigned VAO;
	glGenVertexArrays(1, &VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// COLOR (RGBA)
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	// OVERRIDES THE FIRST glBindBuffer CODE - glBindBuffer(GL_ARRAY_BUFFER, 0);
	// OR USE glNamedBufferData(VBO, sizeof(vertices), vertices, GL_STATIC_DRAW);
	/*
	int success;
	
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	
	if (!success) 
	{
		char infoLog[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		printf("ERROR::SHADER::VETEX::COMPILATION_FAILED\n%s", infoLog);
	}

	//create and compile fragment shader 
	
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		printf("ERROR::FRAGMENT::VETEX::COMPILATION_FAILED\n%s", infoLog);
	}

	// create a shader program, link
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
		printf("ERROR::PROGRAM::LINKING_FAILED\n%s", infoLog);
	}

	glUseProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	*/

	//Render loop
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		// INPUT
		float time = (float)glfwGetTime();

		glClearColor(0.3f, 0.4f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// UPDATE
		ourShader.use();
		glBindVertexArray(VAO);
		// DRAW
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//Clear framebuffer
		
		// Set Time Uniform
		// int timeLoc = glGetUniformLocation(shaderProgram, "uTime");
		// glUniform1f(timeLoc, time);

		//Drawing happens here!
		glfwSwapBuffers(window);
	}
	printf("Shutting down...");
}
