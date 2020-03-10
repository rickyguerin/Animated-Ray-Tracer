#pragma once
#ifndef READER_H
#define READER_H

#include <fstream>
#include <glm/glm.hpp>

#include "../Illumination/illuminationModel.h"

// Consume one token and check that it matches expected
void consumeToken(std::ifstream& file, const char* expected);

// Read one token from the file and convert to the provided type
int readInt(std::ifstream& file);
float readFloat(std::ifstream& file);
double readDouble(std::ifstream& file);

// Consume property name, then read tokens from the file
glm::ivec4 readColor(std::ifstream& file);
glm::vec3 readPosition(std::ifstream& file);
double readRadius(std::ifstream& file);

// Read illumination models
IlluminationModel* readFlatModel(std::ifstream& file);

#endif