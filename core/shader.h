#ifndef SHADER_H
#define SHADER_H

#include "ew/external/glad.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
public:
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath) 
	{
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		// make sure the files are good with this.
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try 
		{
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			// reading files
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// then closing files
			vShaderFile.close();
			fShaderFile.close();
			// then turning them into strings
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();

		}
		catch (std::ifstream::failure& e) 
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl; // error message
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();
		unsigned int vertex, fragment;

		vertex = glCreateShader(GL_VERTEX_SHADER); // making vertex part
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX"); 

		fragment = glCreateShader(GL_FRAGMENT_SHADER); // making fragment part
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");  

		ID = glCreateProgram(); // making ID part
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM"); 

		glDeleteShader(vertex); // remove to save space
		glDeleteShader(fragment);
	}
	// void functions we will need for later
	void use() 
	{
		glUseProgram(ID);
	}

	void setBool(const std::string& name, bool value) 
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}

	void setInt(const std::string& name, int value)
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}

	void setFloat(const std::string& name, float value)
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}

private:
	void checkCompileErrors(unsigned int shader, std::string type) // this function is just to see if it works
	{
		int success;
		char infoLog[1024];
		if (type != "PROGRAM") 
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success) 
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n ------------------------------------------ " << std::endl;
			}
		}
		else 
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success) 
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n ------------------------------------------------- " << std::endl;
			}
		}
	}
};

#endif