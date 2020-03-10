#include <string>
#include <iostream>

#include "../../header/WorldProgram/reader.h"
#include "../../header/Illumination/illuminationModel.h"
#include "../../header/Illumination/flatModel.h"
#include "../../header/Illumination/phongModel.h"

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

	if (modelName.compare("PHONG") == 0) {
		return readPhongModel(file);
	}

	// Return Flat by defualt
	return readFlatModel(file);
}

// Read the next color as a Flat Illumination Model
IlluminationModel* readFlatModel(std::ifstream& file) {
	return new FlatModel(readVec3(file, "color:"));
}

// Read the next lines as a Phong Illumination Model
IlluminationModel* readPhongModel(std::ifstream& file) {
	return new PhongModel(
		readVec3(file, "diffuseColor:"),
		readVec3(file, "specularColor:"),
		readFloat(file, "ambientConst:"),
		readFloat(file, "diffuseConst:"),
		readFloat(file, "specularConst:"),
		readFloat(file, "specularExp:")
	);
}