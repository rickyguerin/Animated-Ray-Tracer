#include <vector>
#include <string>

#include "../header/world.h"
#include "../header/camera.h"
#include "../header/WorldProgram/cameraProgram.h"

// Turn i into a string padded with 0s up to length n
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
	World world(glm::vec3(0.1f, 0.2f, 0.4f));

	world.addProgram("world/ramp/leftFloor.triangle");
	world.addProgram("world/ramp/rightFloor.triangle");
	world.addProgram("world/ramp/rightLeftWall.triangle");
	world.addProgram("world/ramp/leftRightWall.triangle");

	world.addProgram("world/sun.sphere");
	world.addProgram("world/main.light");

	// Read the CameraProgram
	CameraProgram camProg("world/main.camera");

	// Animation frame information
	const float fps = 60;
	const float duration = 4.0;
	const unsigned frames = fps * duration;

	// Animation timer
	float time = 0.0;
	const float spf = duration / frames;

	// Render frames
	for (int i = 0; i < frames; i++) {
		camProg.getCamera(time).render(world, "../images/temp/output_" + padInt(i, 4) + ".png", 1024, 1024, time);
		time += spf;
	}

	return 0;
}