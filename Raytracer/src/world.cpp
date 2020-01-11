#include "../header/world.h"
#include <iostream>
#include <fstream>

glm::ivec4 World::trace(Ray ray, double time) {

	for (int i = 0; i < objects.size(); i++) {
		if (objects[i].collision(ray, time)) {
			return glm::ivec4(255, 0, 0, 255);
		}
	}

	if (double(rand()) / (double(RAND_MAX) + 1.0) < 0.0005) {
		return glm::ivec4(255, 255, 255, 255);
	}
	else {
		return glm::ivec4(0, 0, 0, 255);
	}
}

void World::add(std::string filename) {
	std::ifstream inf(filename);

	while (inf) {
		std::string token;
		inf >> token;
		std::cout << token << "\n";
	}
}