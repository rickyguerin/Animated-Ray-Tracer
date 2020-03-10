#include <iostream>
#include <fstream>

#include "../../header/WorldProgram/reader.h"
#include "../../header/WorldProgram/sphereProgram.h"
#include "../../header/Shape/sphere.h"
#include "../../header/Illumination/illuminationModel.h"

SphereProgram::SphereProgram(const std::string& filename) {
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
		glm::vec3 position = readVec3(progFile, "center:");
		double radius = readDouble(progFile, "radius:");

		consumeToken(progFile, "}");

		// Create frame from parsed data
		SphereFrame sf{
			timestamp,
			illumination,
			position,
			radius
		};

		frames.push_back(sf);
	}
}

Shape* SphereProgram::getShape(const float time) const {

	// Determine what frame of this program occurs at this time
	int activeFrame = 0;
	for (activeFrame; activeFrame < frames.size() - 1; activeFrame++) {
		if (time < frames[activeFrame + 1].timestamp) {
			break;
		}
	}

	// If the last frame is active, no need to interpolate
	if (activeFrame == frames.size() - 1) {
		return new Sphere(frames[activeFrame].illumination, frames[activeFrame].position, frames[activeFrame].radius);
	}

	// Do linear interpolation
	else {
		SphereFrame now = frames[activeFrame];
		SphereFrame next = frames[activeFrame + 1];

		double t = (time - now.timestamp) / (next.timestamp - now.timestamp);

		IlluminationModel* illumination = now.illumination->interpolate(next.illumination, t);
		glm::vec3 position = glm::mix(now.position, next.position, t);
		double radius = glm::mix(now.radius, next.radius, t);

		return new Sphere(illumination, position, radius);
	}
}