#include <vector>
#include "../header/world.h"
#include "../header/camera.h"
#include "../header/sphere.h"

#include <iostream>
#include <string>

int main() {
	srand(64);

	Sphere leftSphere(glm::vec3(-5, 0, 5), 1);
	Sphere rightSphere(glm::vec3(5, 0, 5), 2);

	World world(std::vector<Sphere>{ leftSphere, rightSphere });

	glm::vec3 pos{ 0, 0, 0 };
	glm::vec3 lookat{ 0, 0, 1 };
	glm::vec3 up{ 0, 1, 0 };

	Camera camera(pos, lookat, up, 4, 3, 1.0f);


	const unsigned fps = 1;
	const float duration = 4.0;
	const unsigned frames = fps * duration;

	std::string baseFilename = "../images/temp/output_";
	std::string extension = ".png";
	std::string filename;

	for (int i = 0; i < frames; i++) {
		filename = baseFilename + std::to_string(i) + extension;
		camera.render(&world, filename, 400, 300);
	}

	return 0;
}