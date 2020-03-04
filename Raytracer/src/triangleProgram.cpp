#include <iostream>
#include <fstream>

#include "../header/triangleProgram.h"
#include "../header/triangle.h"

TriangleProgram::TriangleProgram(const std::string & filename) {
	std::ifstream progFile(filename);
	std::string token;

	// Only parse the provided file if it's a Triangle file
	progFile >> token;
	if (token.compare("TRIANGLE") == 0) {
		while (progFile) {
			// Parse each frame
			progFile >> token;
			if (token.compare("FRAME") == 0) {
				// Parse timestamp
				progFile >> token;
				float timestamp = std::stod(token);

				// Parse vertices
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

				// Create frame from parsed data
				TriangleFrame sf {
					timestamp,
					glm::ivec4(r, g, b, a),
					std::vector<glm::vec3>{
						glm::vec3(x, y, z)
					}
				};

				frames.push_back(sf);
			}
		}
	}
}

Shape * TriangleProgram::getShape(const float time) const {

	// Determine what frame of this program occurs at this time
	int activeFrame = 0;
	for (activeFrame; activeFrame < frames.size() - 1; activeFrame++) {
		if (time < frames[activeFrame + 1].timestamp) {
			break;
		}
	}

	TriangleFrame now = frames[activeFrame];
	TriangleFrame next = frames[activeFrame + 1];

	Shape* triangle;

	// If it's the last frame, no need to interpolate
	if (activeFrame == frames.size() - 1) {
		triangle = new Triangle(now.vertices, now.color);
	}

	// Do linear interpolation
	else {
		double t = (time - now.timestamp) / (next.timestamp - now.timestamp);

		std::vector<glm::vec3> vertices;
		glm::ivec4 color = glm::mix(now.color, next.color, t);

		triangle = new Triangle(vertices, color);
	}

	return triangle;
}