#include <vector>
#include <string>
#include <iostream>

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
	World world(glm::vec3(0.0f, 0.3f, 0.5f));

	world.addProgram("world/hextree/ground/middleLeft.triangle");
	world.addProgram("world/hextree/ground/middleRight.triangle");
	world.addProgram("world/hextree/ground/front.triangle");
	world.addProgram("world/hextree/ground/back.triangle");

	world.addProgram("world/hextree/ground/walls/backLeft.triangle");
	world.addProgram("world/hextree/ground/walls/frontLeft.triangle");
	world.addProgram("world/hextree/ground/walls/backRight.triangle");
	world.addProgram("world/hextree/ground/walls/frontRight.triangle");
	world.addProgram("world/hextree/ground/walls/right.triangle");
	world.addProgram("world/hextree/ground/walls/left.triangle");

	world.addProgram("world/hextree/main.light");

	// Read the CameraProgram
	CameraProgram camProg("world/hextree/main.camera");

	// Animation frame information
	const float fps = 1.0;
	const float duration = 1.0;
	const unsigned frames = fps * duration;

	// Animation timer
	float time = 0.0;
	const float spf = duration / frames;

	// Render frames
	for (int i = 0; i < frames; i++) {
		std::cout << "Rendering frame " << padInt(i, 4) << " / " << padInt(frames - 1, 4) << "\n";
		camProg.getCamera(time).render(world, "../images/temp/output_" + padInt(i, 4), 2048, 2048, time);
		time += spf;
	}

	return 0;
}