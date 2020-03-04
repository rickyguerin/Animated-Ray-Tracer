#pragma once
#ifndef READER_H
#define READER_H

#include <fstream>

// Read one token from the file and convert to the provided type
int readInt(const std::ifstream & file);
float readFloat(const std::ifstream & file);
double readDouble(const std::ifstream& file);

#endif