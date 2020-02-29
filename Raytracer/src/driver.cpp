#include <vector>
#include "../header/world.h"
#include "../header/camera.h"
#include "../header/sphere.h"

#include <iostream>
#include <string>

int main() {
	World world(glm::ivec4(50, 150, 250, 255));
	world.add("world/prog.txt");
	world.add("world/vertSphere.txt");

	glm::vec3 pos{ 0, 0, 2 };
	glm::vec3 lookat{ 0, 0, 0 };
	glm::vec3 up{ 0, 1, 0 };

	Camera camera(pos, lookat, up, 45, 2.0f);

	world.transformToCameraSpace(camera.getMatrix());

	const float fps = 1;
	const float duration = 4.0;
	const unsigned frames = fps * duration;

	float time = 0.0;
	const float spf = duration / frames;

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