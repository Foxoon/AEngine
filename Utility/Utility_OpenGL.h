#pragma once

#include <string>
#include <iostream>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UPWARD,
	DOWNWARD,
	ROTATE_LEFT,
	ROTATE_RIGHT,
	ROTATE_UP, 
	ROTATE_DOWN
};



std::string U_readFile(const char *filePath);

const char* U_getShaderSource(const char* filepath);
bool U_compileShader(unsigned int &vertexShader);
template <typename T> void U_readPointer(T var);

template <typename T> void U_readPointer(T var) {
	printf("\n");
	std::cout << "Adress of the pointer : " << var << std::endl;
	std::cout << "Value of the pointer : " << *var << std::endl;

}