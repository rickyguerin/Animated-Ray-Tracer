#include <iostream>
#include <fstream>
#include <glm/common.hpp>
#include "../../header/WorldProgram/reader.h"
#include "../../header/WorldProgram/triangleProgram.h"
#include "../../header/Shape/triangle.h"
#include "../../header/Math/catmullRom.h"

TriangleProgram::TriangleProgram(const std::string& filename) {
	std::ifstream progFile(filename);
	std::string token;

	// Read global values
	consumeToken(progFile, "GLOBAL");
	consumeToken(progFile, "{");
	const std::string modelName = readIlluminationModelName(progFile, "illumination:");
	consumeToken(progFile, "}");

	while (progFile >> token) {
		// Read one frame of data from the file
		float timestamp = stof(token);
		consumeToken(progFile, "{");

		IlluminationModel* illumination = readIlluminationModel(progFile, modelName);
		glm::vec3 vertex1 = readVec3(progFile, "vertex:");
		glm::vec3 vertex2 = readVec3(progFile, "vertex:");
		glm::vec3 vertex3 = readVec3(progFile, "vertex:");

		consumeToken(progFile, "}");

		// Create frame from parsed data
		TriangleFrame tf{
			timestamp,
			illumination,
			std::vector<glm::vec3> {
				vertex1,
				vertex2,
				vertex3
			}
		};

		frames.push_back(tf);
	}
}

// Interpolate between two sets of vertices
std::vector<glm::vec3> TriangleProgram::interpolateVertices(const int activeFrame, const float t, const std::vector<glm::vec3>& before, const std::vector<glm::vec3>& after) const {

	std::vector<glm::vec3> vertices;
	glm::vec3 p0, p3;

	for (int i = 0; i < 3; i++) {
		p0 = NULL_POINT;
		if (activeFrame > 0) {
			p0 = frames[activeFrame - 1].vertices[i];
		}

		p3 = NULL_POINT;
		if (activeFrame + 2 < frames.size()) {
			p3 = frames[activeFrame + 2].vertices[i];
		}

		vertices.push_back(interpolate(t, p0, before[i], after[i], p3));
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
		std::vector<glm::vec3> vertices = interpolateVertices(activeFrame, t, now.vertices, next.vertices);

		return new Triangle(illumination, vertices);
	}
}