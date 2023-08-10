#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	// Vertex shader code
	std::string vShader = readShader(vertexPath);
	const char* vShaderCode = vShader.c_str();
	// Fragment shader code
	std::string fShader = readShader(fragmentPath);	
	const char* fShaderCode = fShader.c_str();

	int success;
	char* infoLog = nullptr;

	// Creating and compiling vertex Shader
	unsigned int vertex = createShader(vShaderCode, GL_VERTEX_SHADER);
	success = compileShader(vertex);
	if (!success)
	{
		int length;
		glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
		infoLog = (char*)_malloca(length * sizeof(char));
		glGetShaderInfoLog(vertex, length, &length, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
			infoLog << std::endl;
	};

	// Creating and compiling fragment shader
	unsigned int fragment = createShader(fShaderCode, GL_FRAGMENT_SHADER);
	success = compileShader(fragment);
	if (!success)
	{
		int length;
		glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
		infoLog = (char*)_malloca(length * sizeof(char));
		glGetShaderInfoLog(fragment, length, &length, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<
			infoLog << std::endl;
	}

	// Creating and linking shader program
	success = createProgram(vertex, fragment);
	// Checking shader program linking status
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" <<
			infoLog << std::endl;
	}
}

Shader::~Shader()
{
	glDeleteProgram(ID);
}

std::string Shader::readShader(const char* shaderPath)
{
	// retrieve the vertex/fragment source code from filePath
	std::string shaderCode;
	std::ifstream shaderFile;
	// ensure ifstream objects can throw exceptions:
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		shaderFile.open(shaderPath);
		std::stringstream shaderStream;
		// read file’s buffer contents into streams
		shaderStream << shaderFile.rdbuf();
		// close file handlers
		shaderFile.close();
		// convert stream into string
		shaderCode = shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	return shaderCode.c_str();
}

int Shader::createShader(const char* source, unsigned int type)
{
	// Creating shader 
	unsigned int shaderID = glCreateShader(type);
	glShaderSource(shaderID, 1, &source, NULL);
	return shaderID;
}

void Shader::use()
{
	glUseProgram(ID);
}

int Shader::createProgram(unsigned int& vShaderID, unsigned int& fShaderID)
{
	int success;
	ID = glCreateProgram();
	glAttachShader(ID, vShaderID);
	glAttachShader(ID, fShaderID);
	glLinkProgram(ID);
	glValidateProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);

	// Deleting unlinked shader code
	glDeleteShader(vShaderID);
	glDeleteShader(fShaderID);

	return success;
}

int Shader::compileShader(unsigned int& shaderID)
{
	int success;
	// compiling Shader
	glCompileShader(shaderID);
	// returning shader compilation status
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	return success;
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
