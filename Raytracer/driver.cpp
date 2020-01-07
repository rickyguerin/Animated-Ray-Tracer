#include "camera.h"

int main() {
	glm::vec3 pos{ 0, 0, 0 };
	glm::vec3 lookat{ 0, 0, 1 };
	glm::vec3 up{ 0, 1, 0 };

	Camera camera(pos, lookat, up, 16, 9, 1.0f);
	camera.render("../images/output.png", 960, 540);

	return 0;
}