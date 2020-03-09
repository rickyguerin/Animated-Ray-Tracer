#pragma once
#ifndef READER_H
#define READER_H

#include <fstream>
#include <glm/glm.hpp>

#include "../Illumination/illuminationModel.h"

// Consume either a { or }
void consumeParen(std::ifstream& file);

// Read one token from the file and convert to the provided type
int readInt(std::ifstream& file);
float readFloat(std::ifstream& file);
double readDouble(std::ifstream& file);

// Read several tokens from the file and convert to a complex type
glm::vec3 readPosition(std::ifstream & file);
glm::ivec4 readColor(std::ifstream & file);

// Read illumination models
IlluminationModel* readFlatModel(std::ifstream& file);

#endif