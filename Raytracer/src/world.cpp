#include "../header/world.h"
#include "../header/WorldProgram/sphereProgram.h"
#include "../header/WorldProgram/triangleProgram.h"
#include "../header/Shape/shape.h"
#include "../header/Data/intersection.h"

World::World(const glm::vec3& color) {
	backgroundColor = color;
}

World::~World() {
	for (const ShapeProgram* prog : programs) {
		delete prog;
	}
}

void World::addProgram(const std::string& filename) {
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

void World::loadShapes(const glm::mat4& cameraMatrix, const float time) {
	for (int i = 0; i < programs.size(); i++) {
		Shape* shape = programs[i]->getShape(time);
		shape->transformToCameraSpace(cameraMatrix);
		currentShapes.push_back(shape);
	}
}

void World::clearShapes() {
	for (int i = 0; i < programs.size(); i++) {
		delete currentShapes[i];
	}

	currentShapes.clear();
}

glm::vec3 World::trace(const glm::vec3& ray, const float time) const {

	// Determine what Shape is intersected by ray first
	Intersection closestIntersection = NULL_INTERSECTION;
	const Shape* intersectedShape = currentShapes[0];

	Intersection currentIntersection;
	for (int i = 0; i < currentShapes.size(); i++) {

		currentIntersection = currentShapes[i]->collision(ray);

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

	// Illuminate the intersected Shape
	else { return intersectedShape->illuminate(); }
}