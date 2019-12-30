#include <glm/vec3.hpp>
#include "ray.cpp"

class Sphere {
private:
	glm::vec3 pos;
	float radius;

public:
	Sphere(glm::vec3 pos, float radius) {
		this->pos = pos;
		this->radius = radius;
	}

	glm::vec3 getPos() {
		return pos;
	}

	float getRadius() {
		return radius;
	}

	bool collision(Ray r) {
		glm::vec3 oc = r.getOrigin() - pos;

		return false;
	}
};