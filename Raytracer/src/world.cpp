#include "../header/world.h"
#include "../header/WorldProgram/sphereProgram.h"
#include "../header/WorldProgram/triangleProgram.h"
#include "../header/Shape/shape.h"
#include "../header/Math/intersection.h"

World::World(const glm::vec3& color) {
	backgroundColor = color;
}

World::~World() {
	for (const ShapeProgram* prog : programs) {
		delete prog;
	}
}

void World::addProgram(const std::string& filename) {
	// Position of dot in name.light
	size_t lightExt = filename.length() - 6;
	assert(lightExt > 0);

	// File is .light
	if (filename.substr(lightExt).compare(".light") == 0) {
		lightPrograms.push_back(LightProgram(filename));
		return;
	}

	// Position of dot in name.sphere
	size_t sphereExt = filename.length() - 7;
	assert(sphereExt > 0);

	// File is .sphere
	if (filename.substr(sphereExt).compare(".sphere") == 0) {
		programs.push_back(new SphereProgram(filename));
		return;
	}

	// Position of dot in name.triangle
	size_t triangleExt = filename.length() - 9;
	assert(triangleExt > 0);

	// File is .triangle
	if (filename.substr(triangleExt).compare(".triangle") == 0) {
		programs.push_back(new TriangleProgram(filename));
		return;
	}
}

void World::loadCurrent(const glm::mat4& cameraMatrix, const float time) {
	// Load Shapes
	for (int i = 0; i < programs.size(); i++) {
		Shape* shape = programs[i]->getShape(time);
		shape->transformToCameraSpace(cameraMatrix);
		currentShapes.push_back(shape);
	}

	// Load Lights
	for (int i = 0; i < lightPrograms.size(); i++) {
		Light light = lightPrograms[i].getLight(time);
		light.transformToCameraSpace(cameraMatrix);
		currentLights.push_back(light);
	}
}

void World::deleteCurrent() {
	for (int i = 0; i < programs.size(); i++) {
		delete currentShapes[i];
	}

	currentShapes.clear();
	currentLights.clear();
}

glm::vec3 World::trace(const glm::vec3& ray, const float time) const {

	// Determine what Shape is intersected by ray first
	Intersection closestIntersection = NULL_INTERSECTION;
	const Shape* intersectedShape = currentShapes[0];

	glm::vec3 origin = glm::vec3(0, 0, 0);
	Intersection currentIntersection;
	for (int i = 0; i < currentShapes.size(); i++) {

		currentIntersection = currentShapes[i]->collision(origin, ray);

		// No intersection occured with this Shape
		if (currentIntersection.isNull()) { continue; }

		// If this intersection is closer than the previous closest, update
		else if (closestIntersection.isNull() || currentIntersection.omega < closestIntersection.omega) {
			closestIntersection = currentIntersection;
			intersectedShape = currentShapes[i];
		}
	}

	// No intersection occurred at all
	if (closestIntersection.isNull()) { return backgroundColor; }

	// Intersection occurred, test for shadow
	else {
		Intersection closestShadowIntersection = NULL_INTERSECTION;
		const Shape* shadowIntersectionShape = currentShapes[0];

		// Test if any light can reach intersection point
		for (int i = 0; i < currentLights.size(); i++) {
			glm::vec3 srd = glm::normalize(currentLights[i].position - closestIntersection.point);
			glm::vec3 sro = closestIntersection.point + (0.01f * srd);
			float lightOmega = (currentLights[i].position - closestIntersection.point).length();

			for (int k = 0; k < currentShapes.size(); k++) {
				currentIntersection = currentShapes[i]->collision(sro, srd);

				// No intersection occured with this Shape
				if (currentIntersection.isNull()) { continue; }

				// If this intersection is closer than the previous closest, update
				else if (closestShadowIntersection.isNull() || currentIntersection.omega < closestShadowIntersection.omega) {
					closestShadowIntersection = currentIntersection;
					shadowIntersectionShape = currentShapes[i];
				}
			}

			// If no shadow ray Intersection, illuminate normally
			if (closestShadowIntersection.isNull()) {
				return intersectedShape->illuminate(closestIntersection, currentLights, false);
			}
		}

		// If every light is blocked, return black
		//return glm::vec3(0, 0, 0);
		return intersectedShape->illuminate(closestIntersection, currentLights, true);
	}
}