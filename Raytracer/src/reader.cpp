#include <string>
#include <iostream>

#include "../header/reader.h"

int readInt(std::ifstream & file) {
	std::string token;
	file >> token;

	return std::stoi(token);
}