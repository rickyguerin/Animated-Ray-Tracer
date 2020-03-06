#include <string>
#include <iostream>

#include "../header/reader.h"

// A string that every method can read into
std::string token;

// Read the next token as an int
int readInt(std::ifstream & file) {
	file >> token;
	return std::stoi(token);
}

// Read the next token as a float
float readFloat(std::ifstream & file) {
	file >> token;
	return std::stof(token);
}

// Read the next token as a double
double readDouble(std::ifstream & file) {
	file >> token;
	return std::stod(token);
}

// Read the next three tokens as a vec3
glm::vec3 readPosition(std::ifstream & file) {

	glm::vec3 position = glm::ivec4();

	for (int i = 0; i < 3; i++) {
		file >> token;
		position[i] = std::stof(token);
	}

	return position;
}

// Read the next four tokens as a vec3
glm::ivec4 readColor(std::ifstream & file) {
	glm::ivec4 color = glm::ivec4();

	for (int i = 0; i < 4; i++) {
		file >> token;
		color[i] = std::stoi(token);
	}

	return color;
}