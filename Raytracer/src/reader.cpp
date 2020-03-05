#include <string>
#include <iostream>

#include "../header/reader.h"

// A string that every method can read into
std::string token;

// Read the next token of the file as an int
int readInt(std::ifstream & file) {
	file >> token;
	return std::stoi(token);
}