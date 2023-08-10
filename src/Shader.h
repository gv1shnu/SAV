#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get the required OpenGL headers
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
	public:
		// constructor reads and builds the shader
		Shader(const char* vertexPath, const char* fragmentPath);
		~Shader();
		// Reads shader code
		std::string readShader(const char* shaderPath);
		// Creates shader
		int createShader(const char* source, unsigned int type);
		// Compiles shader
		int compileShader(unsigned int& shaderID);
		// use/activate the shader
		void use();
		// creating shader program
		int createProgram(unsigned int& vShaderID, unsigned int& fShaderID);

		// utility uniform functions
		void setBool(const std::string& name, bool value) const;
		void setInt(const std::string& name, int value) const;
		void setFloat(const std::string& name, float value) const;
	private:
		// the program ID
		unsigned int ID;
};

#endif