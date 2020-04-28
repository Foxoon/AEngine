#include <stdio.h>
#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


using namespace std;



std::string U_readFile(const char *filePath) {
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);

	if (!fileStream.is_open()) {
		std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
		return "";
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

const char* U_getShaderSource(const char* filepath) {
	std::string shaderStr = U_readFile(filepath);
	
	const char* shaderSource = shaderStr.c_str();

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &shaderSource, NULL);
	
	
	return shaderSource;
}

bool U_compileShader(unsigned int &vertexShader) {

	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	return success;
}



