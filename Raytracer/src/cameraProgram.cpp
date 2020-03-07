#include <iostream>
#include <fstream>

#include "../header/cameraProgram.h"
#include "../header/reader.h"

CameraProgram::CameraProgram(const std::string & filename) {
	std::ifstream progFile(filename);
	std::string token;

	// Only parse the provided file if it's a Camera file
	progFile >> token;
	if (token.compare("CAMERA") == 0) {
		while (progFile >> token) {
			// Parse each frame
			if (token.compare("FRAME") == 0) {
				// Read one frame of data from the file
				float timestamp = readFloat(progFile);

				glm::vec3 eye = readPosition(progFile);
				glm::vec3 lookat = readPosition(progFile);
				glm::vec3 up = readPosition(progFile);

				float focalLength = readFloat(progFile);
				float canvasWidth = readFloat(progFile);
				float canvasHeight = readFloat(progFile);

				// Create frame from parsed data
				CameraFrame cf {
					timestamp,
					eye, lookat, up,
					focalLength, canvasWidth, canvasHeight
				};

				frames.push_back(cf);
			}
		}
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