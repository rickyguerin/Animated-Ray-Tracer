#include <vector>
#include <string>

#include "../header/world.h"
#include "../header/camera.h"
#include "../header/sphere.h"
#include "../header/sphereProgram.h";
#include "../header/triangleProgram.h"

std::string padInt(int i, int n) {

	int numZeros = n - 1;
	int copy = i / 10;

	while (copy > 0) {
		numZeros--;
		copy /= 10;
	}

	std::string pad = "";
	pad.append("0000000000", numZeros);

	return pad + std::to_string(i);
}

int main() {
	// Create the World
	World world(glm::ivec4(0, 0, 0, 255));

	world.addProgram(new SphereProgram("world/anim2.sphere"));
	world.addProgram(new TriangleProgram("world/leftFloor.triangle"));
	world.addProgram(new TriangleProgram("world/rightFloor.triangle"));

	// Create the Camera
	glm::vec3 pos{ 0, 1, 4 };
	glm::vec3 lookat{ 0, 1, 0 };
	glm::vec3 up{ 0, 1, 0 };

	Camera camera(pos, lookat, up, 45, 2.0f);

	// Animation frame information
	const float fps = 1;
	const float duration = 1.0;
	const unsigned frames = fps * duration;

	// Animation timer
	float time = 0.0;
	const float spf = duration / frames;

	// Render frames
	for (int i = 0; i < frames; i++) {
		camera.render(world, "../images/temp/output_" + padInt(i, 4) + ".png", 400, 400, time);
		time += spf;
	}

	return 0;
}