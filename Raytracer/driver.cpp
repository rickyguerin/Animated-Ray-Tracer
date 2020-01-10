#include <vector>
#include "world.h"
#include "camera.h"
#include "sphere.h"


int main() {
	srand(420420);

	Sphere leftSphere(glm::vec3(-2, 0, 5), 1);
	Sphere rightSphere(glm::vec3(2, 0, 5), 1);

	World world(std::vector<Sphere>{ leftSphere, rightSphere});

	glm::vec3 pos{ 0, 0, 0 };
	glm::vec3 lookat{ 0, 0, 1 };
	glm::vec3 up{ 0, 1, 0 };

	Camera camera(pos, lookat, up, 16, 9, 1.0f);
	camera.render(&world, "../images/output.png", 960, 540);

	return 0;
}