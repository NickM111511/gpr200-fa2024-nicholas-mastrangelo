#include <stdio.h>
#include <math.h>

#include <ew/external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <ew/external/stb_image.h>

#include <iostream>
#include <shader.h>

// #define STB_IMAGE_IMPLEMENTATION
// #include "stb_image.h"



const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

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
	// end of window section // start of verticies section ---
	Shader ourShader("assets/Vertexshader.vert","assets/Fragmentshader.frag");

	float vertices[] = {
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};
	// end of verticies section // start of buffer section ---
	unsigned VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// COLOR (RGBA)
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
	// end of buffer section // start of texture section ---
	unsigned int texture1, texture2;

	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	/*
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(FileSystem::getPath("Input file here").c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_inage_free(data);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load(FileSystem::getPath("Input file here").c_str(), &width, &height, &nrChammels, 0);
	if(data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	ourShader.use();
	glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
	ourShader.setInt("texture2", 1);
	*/
	// end of texture section // start of render loop ---

	//glBlendFunc(2 params);
	//glBlendEquation();


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
