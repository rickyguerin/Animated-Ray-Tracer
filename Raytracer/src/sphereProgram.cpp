#include <iostream>
#include <fstream>

#include "../header/sphereProgram.h"
#include "../header/sphere.h"
#include "../header/reader.h"

SphereProgram::SphereProgram(const std::string & filename) {
	std::ifstream progFile(filename);
	std::string token;

	// Only parse the provided file if it's a Sphere file
	progFile >> token;
	if (token.compare("SPHERE") == 0) {
		while (progFile >> token) {
			// Parse each frame
			if (token.compare("FRAME") == 0) {
				// Read one frame of data from the file
				float timestamp = readFloat(progFile);
				glm::vec3 position = readPosition(progFile);
				glm::ivec4 color = readColor(progFile);
				double radius = readDouble(progFile);

				// Create frame from parsed data
				SphereFrame sf {
					timestamp,
					color,
					position,
					radius
				};

				frames.push_back(sf);
			}
		}
	}
}

Shape * SphereProgram::getShape(const float time) const {

	// Determine what frame of this program occurs at this time
	int activeFrame = 0;
	for (activeFrame; activeFrame < frames.size() - 1; activeFrame++) {
		if (time < frames[activeFrame + 1].timestamp) {
			break;
		}
	}

	// If the last frame is active, no need to interpolate
	if (activeFrame == frames.size() - 1) {
		return new Sphere(frames[activeFrame].position, frames[activeFrame].color, frames[activeFrame].radius);
	}

	// Do linear interpolation
	else {
		SphereFrame now = frames[activeFrame];
		SphereFrame next = frames[activeFrame + 1];

		double t = (time - now.timestamp) / (next.timestamp - now.timestamp);

		glm::vec3 position = glm::mix(now.position, next.position, t);
		glm::ivec4 color = glm::mix(now.color, next.color, t);
		double radius = glm::mix(now.radius, next.radius, t);

		return new Sphere(position, color, radius);
	}
}