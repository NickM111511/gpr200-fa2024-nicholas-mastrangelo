#include <stdio.h>
#include <math.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <ew/external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <random>
#include <iostream>
#include <shader.h>
#include <camera.h>

#define STB_IMAGE_IMPLEMENTATION
#include <ew/external/stb_image.h>

// needs to be called for camera controls
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// this is used for the randomization factor for the cubes
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> r_speed(1, 45);
std::uniform_int_distribution<> c_size(1, 3);
std::uniform_int_distribution<> x_axis(-5, 5);
std::uniform_int_distribution<> y_axis(-6, 6);
std::uniform_int_distribution<> z_axis(-15, 0);

// variables being initialized for later use
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;
const int TOTAL_CUBES = 20;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f)); // for the camera

bool firstMouse = true; // movement variables
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = 1080.0f / 2.0f;
float lastY = 720.0f / 2.0f;
float fov = 60.0f;

float cube_r[TOTAL_CUBES]; // for the cubes 
float cubeSize[TOTAL_CUBES];

float deltaTime = 0.0f; // time variables
float lastFrame = 0.0f;

glm::vec3 lightPos(-1.2f, 1.0f, -2.0f); // for lighting

int main() {
	// Initialization of program --- 
	printf("Initializing...");
	if (!glfwInit()) {
		printf("GLFW failed to init!");
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Assignment 5 Thing", NULL, NULL);
	if (window == NULL) {
		printf("GLFW failed to create window");
		return 1;
	}

	glfwMakeContextCurrent(window);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGL(glfwGetProcAddress)) {
		printf("GLAD Failed to load GL headers");
		return 1;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// end of window section // start of verticies section --- 
	Shader lightingShader("assets/basic_light.vert", "assets/basic_light.frag"); // lighting shader
	Shader lightCubeShader("assets/light_cube.vert", "assets/light_cube.frag"); // cube with the lighting 
	Shader transformShader("assets/transform.vert","assets/transform.frag"); // this is for the 20 cubes

	// assignment 5 verts, 6x8 for each side of the cube
	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};

	// random places for cubes  
	glm::vec3 cubePositions[TOTAL_CUBES];

	// this is to make each cube rotate uniquely
	for (int i = 0; i < TOTAL_CUBES; i++)
	{
		cube_r[i] = r_speed(gen);
	}

	// this is to make each cube size uniquely
	for (int i = 0; i < TOTAL_CUBES; i++)
	{
		cubeSize[i] = c_size(gen);
	}

	// this is to make each position uniquely
	for (int i = 0; i < TOTAL_CUBES; i++)
	{
		cubePositions[i] = glm::vec3(x_axis(gen), y_axis(gen), z_axis(gen));
	}

	// end of verticies section // start of buffer section ---
	// this part is for the cubes
	unsigned VBO, cubeVAO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(cubeVAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); 
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 6)); 
	glEnableVertexAttribArray(2); 

	// this part is for the cube after lighting
	unsigned int lightCubeVAO;
	glGenVertexArrays(1, &lightCubeVAO);
	glBindVertexArray(lightCubeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// end of buffer section // start of texture section --- // assignment 4 thing, remove if not needed
	
	// vairables needed to load data image
	unsigned int texture1, texture2;
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("assets/det.png", &width, &height, &nrChannels, 0); // initalizes with det, if not using it anymore then change this.

	// 1st texture (aka det)
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// loading the textures
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
    

	//2nd texture (aka boxside)
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// loading the texture
	data = stbi_load("assets/boxside.png", &width, &height, &nrChannels, 0);
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
	
	// using the textures here

	// old assignment 4 things, remove later 
	 transformShader.use();
	 transformShader.setInt("texture1", 0); // not using det right now
	 transformShader.setInt("texture2", 1);

	// end of texture section // start of render loop ---

	//Render loop
	while (!glfwWindowShouldClose(window)) {

		// time variables
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		// render starting
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// camera starting
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();

		/*
		lightingShader.use(); // calls for lightingShader properties
		lightingShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
		lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("lightPos", lightPos);
		lightingShader.setVec3("viewPos", camera.Position);
		lightingShader.setMat4("projection", projection);
		lightingShader.setMat4("view", view);
		lightingShader.setInt("blinn", true); // needed later
		*/

		transformShader.use(); 
		transformShader.setMat4("projection", projection);
		transformShader.setMat4("view", view);
		glBindVertexArray(cubeVAO);

		// binding textures
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		transformShader.setInt("texture1", 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		transformShader.setInt("texture2", 1);

		for (unsigned int i = 0; i < TOTAL_CUBES; i++) // making each cube here
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			model = glm::scale(model, glm::vec3(cubeSize[i]));
			float angle = cube_r[i] * (deltaTime + 1); //  * glfwGetTime() // for them to constantly rotate
			model = glm::rotate(model, glm::radians(angle), glm::vec3(0.8f, 0.3f, 0.5f));
			transformShader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		/*

		lightCubeShader.use();
		lightCubeShader.setMat4("projection", projection);
		lightCubeShader.setMat4("view", view);
		
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		lightCubeShader.setMat4("model", model);

		// glBindVertexArray(lightCubeVAO);
		// glDrawArrays(GL_TRIANGLES, 0, 36);

		// code not being used.
		*/

		//Drawing happens here!
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	printf("Shutting down...");
}

// this is for the camera movement
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) 
	{
		camera.ProcessKeyboard(SPRINT, deltaTime);
	}
		
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}
		
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}
		
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(LEFT, deltaTime);
	}
		
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}
		
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(DOWN, deltaTime);
	}
		
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(UP, deltaTime);
	}
		
}

// this is for the mouse movement function
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// this if for the scroll function
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}


