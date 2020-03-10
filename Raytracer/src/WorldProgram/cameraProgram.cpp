#include <iostream>
#include <fstream>

#include "../../header/WorldProgram/cameraProgram.h"
#include "../../header/WorldProgram/reader.h"

CameraProgram::CameraProgram(const std::string& filename) {
	std::ifstream progFile(filename);
	std::string token;

	while (progFile >> token) {
		// Read one frame of data from the file
		float timestamp = stof(token);
		consumeToken(progFile, "{");

		glm::vec3 eye = readVec3(progFile, "eye:");
		glm::vec3 lookat = readVec3(progFile, "lookat:");
		glm::vec3 up = readVec3(progFile, "up:");

		float focalLength = readFloat(progFile, "focalLength:");
		float canvasWidth = readFloat(progFile, "canvasWidth:");
		float canvasHeight = readFloat(progFile, "canvasHeight:");

		consumeToken(progFile, "}");

		// Create frame from parsed data
		CameraFrame cf{
			timestamp,
			eye, lookat, up,
			focalLength, canvasWidth, canvasHeight
		};

		frames.push_back(cf);
	}
}

Camera CameraProgram::getCamera(const float time) const {
	// Determine what frame of this program occurs at this time
	int activeFrame = 0;
	for (activeFrame; activeFrame < frames.size() - 1; activeFrame++) {
		if (time < frames[activeFrame + 1].timestamp) {
			break;
		}
	}

	// If the last frame is active, no need to interpolate
	if (activeFrame == frames.size() - 1) {
		return Camera(frames[activeFrame].eye, frames[activeFrame].lookat, frames[activeFrame].up,
			frames[activeFrame].focalLength, frames[activeFrame].canvasWidth, frames[activeFrame].canvasHeight);
	}

	// Do linear interpolation
	else {
		CameraFrame now = frames[activeFrame];
		CameraFrame next = frames[activeFrame + 1];

		double t = (time - now.timestamp) / (next.timestamp - now.timestamp);

		glm::vec3 eye = glm::mix(now.eye, next.eye, t);
		glm::vec3 lookat = glm::mix(now.lookat, next.lookat, t);
		glm::vec3 up = glm::mix(now.up, next.up, t);

		float focalLength = glm::mix(now.focalLength, next.focalLength, t);
		float canvasWidth = glm::mix(now.canvasWidth, next.canvasWidth, t);
		float canvasHeight = glm::mix(now.canvasHeight, next.canvasHeight, t);

		return Camera(eye, lookat, up, focalLength, canvasWidth, canvasHeight);
	}
}