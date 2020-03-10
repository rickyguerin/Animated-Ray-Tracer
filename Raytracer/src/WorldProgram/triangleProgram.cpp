#include <iostream>
#include <fstream>

#include "../../header/WorldProgram/reader.h"
#include "../../header/WorldProgram/triangleProgram.h"
#include "../../header/Shape/triangle.h"

TriangleProgram::TriangleProgram(const std::string& filename) {
	std::ifstream progFile(filename);
	std::string token;

	while (progFile >> token) {
		if (token.compare("FRAME") == 0) {
			// Read one frame of data from the file
			float timestamp = readFloat(progFile);
			IlluminationModel* illumination = readFlatModel(progFile);
			glm::vec3 vertexOne = readPosition(progFile);
			glm::vec3 vertexTwo = readPosition(progFile);
			glm::vec3 vertexThree = readPosition(progFile);

			// Create frame from parsed data
			TriangleFrame tf{
				timestamp,
				illumination,
				std::vector<glm::vec3> {
					vertexOne,
					vertexTwo,
					vertexThree
				}
			};

			frames.push_back(tf);
		}
	}
}

// Interpolate between two sets of vertices
std::vector<glm::vec3> interpolateVertices(const std::vector<glm::vec3>& before, const std::vector<glm::vec3>& after, const float t) {

	std::vector<glm::vec3> vertices;

	for (int i = 0; i < 3; i++) {
		vertices.push_back(glm::mix(before[i], after[i], t));
	}

	return vertices;
}

Shape* TriangleProgram::getShape(const float time) const {

	// Determine what frame of this program occurs at this time
	int activeFrame = 0;
	for (activeFrame; activeFrame < frames.size() - 1; activeFrame++) {
		if (time < frames[activeFrame + 1].timestamp) {
			break;
		}
	}

	// If the last frame is active, no need to interpolate
	if (activeFrame == frames.size() - 1) {
		return new Triangle(frames[activeFrame].illumination, frames[activeFrame].vertices);
	}

	// Do linear interpolation
	else {
		TriangleFrame now = frames[activeFrame];
		TriangleFrame next = frames[activeFrame + 1];

		double t = (time - now.timestamp) / (next.timestamp - now.timestamp);

		IlluminationModel* illumination = now.illumination->interpolate(next.illumination, t);
		std::vector<glm::vec3> vertices = interpolateVertices(now.vertices, next.vertices, t);

		return new Triangle(illumination, vertices);
	}
}