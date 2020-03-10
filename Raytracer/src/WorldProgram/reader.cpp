#include <string>
#include <iostream>

#include "../../header/WorldProgram/reader.h"
#include "../../header/Illumination/illuminationModel.h"
#include "../../header/Illumination/flatModel.h"

// A string that every method can read into
std::string token;

// Consume one token and check that it matches expected
void consumeToken(std::ifstream& file, const char* expected) {
	file >> token;
	assert(token.compare(expected) == 0);
}

// Consume the attribute token, and read the following token as an int
int readInt(std::ifstream& file, const char* attribute) {
	consumeToken(file, attribute);
	file >> token;
	return std::stoi(token);
}

// Consume the attribute token, and read the following token as a float
float readFloat(std::ifstream& file, const char* attribute) {
	consumeToken(file, attribute);
	file >> token;
	return std::stof(token);
}

// Consume the attribute token, and read the following token as a double
double readDouble(std::ifstream& file, const char* attribute) {
	consumeToken(file, attribute);
	file >> token;
	return std::stod(token);
}

// Consume the attribute token, and read the following tokens as a vec3
glm::vec3 readVec3(std::ifstream& file, const char* attribute) {
	consumeToken(file, attribute);

	glm::vec3 vec = glm::vec3();
	
	for (int i = 0; i < 3; i++) {
		file >> token;
		vec[i] = std::stof(token);
	}

	return vec;
}

// Consume the attribute token, and read the following tokens as an ivec4
glm::ivec4 readIVec4(std::ifstream& file, const char* attribute) {
	consumeToken(file, attribute);

	glm::ivec4 vec = glm::ivec4();

	for (int i = 0; i < 4; i++) {
		file >> token;
		vec[i] = std::stoi(token);
	}

	return vec;
}

std::string readIlluminationModelName(std::ifstream& file, const char* attribute) {
	consumeToken(file, attribute);

	file >> token;

	// Check that token is a valid IlluminationModel name
	assert(
		token.compare("FLAT") == 0 ||
		token.compare("PHONG") == 0
	);

	return token;
}

IlluminationModel* readIlluminationModel(std::ifstream& file, const std::string& modelName) {
	if (modelName.compare("FLAT") == 0) { return readFlatModel(file); }
	//if (name.compare("PHONG") == 0) { return readPhongModel(file); }
}

// Read the next four tokens as a Flat Illumination Model
IlluminationModel* readFlatModel(std::ifstream& file) {
	return new FlatModel(readIVec4(file, "color:"));
}