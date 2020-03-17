#include <iostream>
#include <fstream>
#include <glm/common.hpp>
#include "../../header/WorldProgram/lightProgram.h"
#include "../../header/WorldProgram/reader.h"

LightProgram::LightProgram(const std::string& filename) {
	std::ifstream progFile(filename);
	std::string token;

	while (progFile >> token) {
		// Read one frame of data from the file
		float timestamp = stof(token);
		consumeToken(progFile, "{");

		glm::vec3 position = readVec3(progFile, "position:");
		glm::vec3 color = readVec3(progFile, "color:");

		consumeToken(progFile, "}");

		// Create frame from parsed data
		LightFrame cf{
			timestamp,
			position,
			color
		};

		frames.push_back(cf);
	}
}

Light LightProgram::getLight(const float time) const {
	// Determine what frame of this program occurs at this time
	int activeFrame = 0;
	for (activeFrame; activeFrame < frames.size() - 1; activeFrame++) {
		if (time < frames[activeFrame + 1].timestamp) {
			break;
		}
	}

	// If the last frame is active, no need to interpolate
	if (activeFrame == frames.size() - 1) {
		return Light{ frames[activeFrame].position, frames[activeFrame].color };
	}

	// Do linear interpolation
	else {
		LightFrame now = frames[activeFrame];
		LightFrame next = frames[activeFrame + 1];

		double t = (time - now.timestamp) / (next.timestamp - now.timestamp);

		glm::vec3 position = glm::mix(now.position, next.position, t);
		glm::vec3 color = glm::mix(now.color, next.color, t);

		return Light{ position, color };
	}
}