#include <iostream>
#include <fstream>

#include "../header/sphereProgram.h"
#include "../header/sphere.h"

SphereProgram::SphereProgram(const std::string & filename) {
	std::ifstream progFile(filename);
	std::string token;

	// Only parse the provided file if it's a Sphere file
	progFile >> token;
	if (token.compare("SPHERE") == 0) {
		while (progFile) {
			// Parse each frame
			progFile >> token;
			if (token.compare("FRAME") == 0) {
				// Parse timestamp
				progFile >> token;
				float timestamp = std::stod(token);

				// Parse position
				progFile >> token;
				float x = std::stod(token);

				progFile >> token;
				float y = std::stod(token);

				progFile >> token;
				float z = std::stod(token);

				// Parse color
				progFile >> token;
				int r = std::stoi(token);

				progFile >> token;
				int g = std::stoi(token);

				progFile >> token;
				int b = std::stoi(token);

				progFile >> token;
				int a = std::stoi(token);

				// Parse radius
				progFile >> token;
				double radius = std::stod(token);

				// Create frame from parsed data
				SphereFrame sf {
					timestamp,
					glm::ivec4(r, g, b, a),
					glm::vec3(x, y, z),
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

	SphereFrame now = frames[activeFrame];
	SphereFrame next = frames[activeFrame + 1];

	Shape* sphere;

	// If it's the last frame, no need to interpolate
	if (activeFrame == frames.size() - 1) {
		sphere = new Sphere(now.position, now.color, now.radius);
	}

	// Do linear interpolation
	else {
		double t = (time - now.timestamp) / (next.timestamp - now.timestamp);

		glm::vec3 position = glm::mix(now.position, next.position, t);
		glm::ivec4 color = glm::mix(now.color, next.color, t);
		double radius = glm::mix(now.radius, next.radius, t);

		sphere = new Sphere(position, color, radius);
	}

	return sphere;
}