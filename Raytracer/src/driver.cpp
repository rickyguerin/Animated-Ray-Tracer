#include <vector>
#include "../header/world.h"
#include "../header/camera.h"
#include "../header/sphere.h"

#include <iostream>
#include <string>

int main() {
	srand(64);

	World world;
	world.add("world/prog.txt");

	glm::vec3 pos{ 0, 0, 0 };
	glm::vec3 lookat{ 0, 0, 1 };
	glm::vec3 up{ 0, 1, 0 };

	Camera camera(pos, lookat, up, 4, 3, 1.0f);


	const unsigned fps = 2;
	double time = 0.0;
	const double duration = 4.0;
	const unsigned frames = fps * duration;

	const double spf = duration / frames;

	std::string baseFilename = "../images/temp/output_";
	std::string extension = ".png";
	std::string filename;

	for (int i = 0; i < frames; i++) {
		filename = baseFilename + std::to_string(i) + extension;
		camera.render(&world, filename, 400, 300, time);
		time += spf;
	}

	return 0;
}