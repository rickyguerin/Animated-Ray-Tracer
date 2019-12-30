#include <glm/vec3.hpp>

class Ray {
private:
	glm::vec3 origin;
	glm::vec3 direction;

public:
	Ray(glm::vec3 origin) {
		this->origin = origin;
		this->direction = glm::vec3(0, 0, 0);
	}

	Ray(glm::vec3 origin, glm::vec3 direction) {
		this->origin = origin;
		this->direction = direction;
	}

	glm::vec3 getOrigin() {
		return origin;
	}

	glm::vec3 getDirection() {
		return direction;
	}

	void setDirection(glm::vec3 direction) {
		this->direction = direction;
	}
};