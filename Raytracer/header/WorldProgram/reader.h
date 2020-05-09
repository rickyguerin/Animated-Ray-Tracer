#pragma once
#ifndef READER_H
#define READER_H

#include <fstream>
#include <glm/vec3.hpp>

#include "../Illumination/illuminationModel.h"

// Consume one token and check that it matches expected
void consumeToken(std::ifstream& file, const char* expected);

// Read one attribute from the file
int readInt(std::ifstream& file, const char* attribute);
float readFloat(std::ifstream& file, const char* attribute);
double readDouble(std::ifstream& file, const char* attribute);
glm::vec3 readVec3(std::ifstream& file, const char* attribute);

// Read illumination models
std::string readIlluminationModelName(std::ifstream& file, const char* attribute);
IlluminationModel* readIlluminationModel(std::ifstream& file, const std::string& modelName);
IlluminationModel* readFlatModel(std::ifstream& file);
IlluminationModel* readPhongModel(std::ifstream& file);
IlluminationModel* readCheckerModel(std::ifstream& file);
IlluminationModel* readNoiseModel(std::ifstream& file);

#endif