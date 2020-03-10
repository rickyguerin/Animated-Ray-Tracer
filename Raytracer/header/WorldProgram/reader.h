#pragma once
#ifndef READER_H
#define READER_H

#include <fstream>
#include <glm/glm.hpp>

#include "../Illumination/illuminationModel.h"

// Consume one token and check that it matches expected
void consumeToken(std::ifstream& file, const char* expected);

// Read one basic attribute from the file
int readInt(std::ifstream& file, const char* attribute);
float readFloat(std::ifstream& file, const char* attribute);
double readDouble(std::ifstream& file, const char* attribute);

// Read one complex attribute from the file
glm::vec3 readVec3(std::ifstream& file, const char* attribute);
glm::ivec4 readIVec4(std::ifstream& file, const char* attribute);

// Read illumination models
std::string readIlluminationModelName(std::ifstream& file, const char* attribute);
IlluminationModel* readIlluminationModel(std::ifstream& file, const std::string& modelName);
IlluminationModel* readFlatModel(std::ifstream& file);

#endif