#include "../header/world.h"
#include <iostream>
#include <fstream>

World::World(glm::ivec4 color) {
	backgroundColor = color;
}

glm::ivec4 World::trace(Ray ray, double time) {

	for (int i = 0; i < objects.size(); i++) {
		if (objects[i].collision(ray, time)) {
			return objects[i].illuminate(time);
		}
	}

	return backgroundColor;
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
				int r = std::stoi(token);

				inf >> token;
				int g = std::stoi(token);

				inf >> token;
				int b = std::stoi(token);

				inf >> token;
				int a = std::stoi(token);
				
				inf >> token;
				double radius = std::stod(token);

				SphereFrame sf {
					timestamp,
					glm::vec3(x, y, z),
					glm::ivec4(r, g, b, a),
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