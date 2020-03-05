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
	file >> token;
	float x = std::stof(token);

	file >> token;
	float y = std::stof(token);

	file >> token;
	float z = std::stof(token);

	return glm::vec3(x, y, z);
}

// Read the next four tokens as a vec3
glm::ivec4 readColor(std::ifstream & file) {
	file >> token;
	int r = std::stoi(token);

	file >> token;
	int g = std::stoi(token);

	file >> token;
	int b = std::stoi(token);

	file >> token;
	int a = std::stoi(token);

	return glm::ivec4(r, g, b, a);
}