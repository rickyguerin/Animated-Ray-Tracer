#include "../header/world.h"
#include <iostream>
#include <fstream>

glm::ivec4 World::trace(Ray ray, double time) {

	for (int i = 0; i < objects.size(); i++) {
		if (objects[i].collision(ray, time)) {
			return glm::ivec4(255, 0, 0, 255);
		}
	}

	return glm::ivec4(0, 0, 0, 255);
}

void World::add(std::string filename) {
	std::ifstream inf(filename);

	std::string token;

	Sphere sphere;

	inf >> token;
	if (token.compare("SPHERE") == 0) {
		while (inf) {
			inf >> token;
			if (token.compare("FRAME") == 0) {
				inf >> token;
				double timestamp = std::stod(token);

				inf >> token;
				double x = std::stod(token);

				inf >> token;
				double y = std::stod(token);
				
				inf >> token;
				double z = std::stod(token);
				
				inf >> token;
				double radius = std::stod(token);

				SphereFrame sf {
					timestamp,
					glm::vec3(x, y, z),
					radius
				};

				sphere.addFrame(sf);
			}
		}

		objects.push_back(sphere);
	}	
}

void World::transformToCameraSpace(glm::mat4 cameraMatrix) {
	for (int i = 0; i < objects.size(); i++) {
		objects[i].transformToCameraSpace(cameraMatrix);
	}
}