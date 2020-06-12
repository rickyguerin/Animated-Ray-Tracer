#include <string>
#include <iostream>

#include "../../header/WorldProgram/reader.h"
#include "../../header/Illumination/illuminationModel.h"
#include "../../header/Illumination/phongModel.h"
#include "../../header/Illumination/checkerModel.h"
#include "../../header/Illumination/noiseModel.h"

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
		token.compare("PHONG") == 0 ||
		token.compare("CHECKER") == 0 ||
		token.compare("NOISE") == 0
	);

	return token;
}

IlluminationModel* readIlluminationModel(std::ifstream& file, const std::string& modelName) {

	if (modelName.compare("CHECKER") == 0) {
		return readCheckerModel(file);
	}

	else if (modelName.compare("NOISE") == 0) {
		return readNoiseModel(file);
	}

	// Return Phong by defualt
	return readPhongModel(file);
}

// Read the next lines as a Phong Illumination Model
IlluminationModel* readPhongModel(std::ifstream& file) {

	glm::vec3 diffuseColor = readVec3(file, "diffuseColor:");
	glm::vec3 specularColor = readVec3(file, "specularColor:");
	float ambientConst = readFloat(file, "ambientConst:");
	float diffuseConst = readFloat(file, "diffuseConst:");
	float specularConst = readFloat(file, "specularConst:");
	float specularExp = readFloat(file, "specularExp:");
	float kReflect = readFloat(file, "kReflect:");
	float kRefract = readFloat(file, "kRefract:");
	float refIndex = readFloat(file, "refIndex:");

	return new PhongModel(
		diffuseColor, specularColor,
		ambientConst, diffuseConst, specularConst, specularExp,
		kReflect, kRefract, refIndex
	);
}

// Read the next lines as a Phong Illumination Model
IlluminationModel* readNoiseModel(std::ifstream& file) {

	glm::vec3 primaryColor = readVec3(file, "primaryColor:");
	glm::vec3 secondaryColor = readVec3(file, "secondaryColor:");
	glm::vec3 specularColor = readVec3(file, "specularColor:");
	float ambientConst = readFloat(file, "ambientConst:");
	float diffuseConst = readFloat(file, "diffuseConst:");
	float specularConst = readFloat(file, "specularConst:");
	float specularExp = readFloat(file, "specularExp:");
	float kReflect = readFloat(file, "kReflect:");
	float kRefract = readFloat(file, "kRefract:");
	float refIndex = readFloat(file, "refIndex:");

	return new NoiseModel(
		primaryColor, specularColor, secondaryColor,
		ambientConst, diffuseConst, specularConst, specularExp,
		kReflect, kRefract, refIndex
	);
}

// Read the next lines as a Checker Illumination Model
IlluminationModel* readCheckerModel(std::ifstream& file) {
	float checkSize = readFloat(file, "checkSize:");
	glm::vec3 primaryColor = readVec3(file, "primaryColor:");
	glm::vec3 secondaryColor = readVec3(file, "secondaryColor:");
	glm::vec3 specularColor = readVec3(file, "specularColor:");
	float ambientConst = readFloat(file, "ambientConst:");
	float diffuseConst = readFloat(file, "diffuseConst:");
	float specularConst = readFloat(file, "specularConst:");
	float specularExp = readFloat(file, "specularExp:");
	float kReflect = readFloat(file, "kReflect:");
	float kRefract = readFloat(file, "kRefract:");
	float refIndex = readFloat(file, "refIndex:");

	return new CheckerModel(
		checkSize, primaryColor, secondaryColor, specularColor,
		ambientConst, diffuseConst, specularConst, specularExp,
		kReflect, kRefract, refIndex
	);
}