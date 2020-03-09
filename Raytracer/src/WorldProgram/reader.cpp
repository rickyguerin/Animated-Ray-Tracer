#include <string>
#include <iostream>

#include "../../header/WorldProgram/reader.h"
#include "../../header/Illumination/illuminationModel.h"
#include "../../header/Illumination/flatModel.h"

// A string that every method can read into
std::string token;

// Consume one token and check that it's a paren
void consumeParen(std::ifstream& file) {
	file >> token;

	bool isLeftParen = token.compare("{") == 0;
	bool isRightParen = token.compare("}") == 0;

	assert(isLeftParen || isRightParen);
}

// Read the next token as an int
int readInt(std::ifstream& file) {
	file >> token;
	return std::stoi(token);
}

// Read the next token as a float
float readFloat(std::ifstream& file) {
	file >> token;
	return std::stof(token);
}

// Read the next token as a double
double readDouble(std::ifstream& file) {
	file >> token;
	return std::stod(token);
}

// Read the next three tokens as a vec3
glm::vec3 readPosition(std::ifstream& file) {

	glm::vec3 position = glm::ivec4();

	for (int i = 0; i < 3; i++) {
		file >> token;
		position[i] = std::stof(token);
	}

	return position;
}

// Read the next four tokens as a ivec4
glm::ivec4 readColor(std::ifstream& file) {
	glm::ivec4 color = glm::ivec4();

	for (int i = 0; i < 4; i++) {
		file >> token;
		color[i] = std::stoi(token);
	}

	return color;
}

// Consume one token and check that it's a paren
double readRadius(std::ifstream& file) {
	file >> token;
	assert(token.compare("radius:") == 0);

	file >> token;
	return std::stod(token);
}

// Read the next four tokens as a Flat Illumination Model
IlluminationModel* readFlatModel(std::ifstream& file) {
	return new FlatModel(readColor(file));
}