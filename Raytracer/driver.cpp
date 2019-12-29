#include "camera.cpp"

int main() {
	glm::vec3 pos{ 0, 0, 0 };
	glm::vec3 lookat{ 0, 0, 1 };
	glm::vec3 up{ 0, 1, 0 };

	Camera camera(pos, lookat, up, 960, 540, 1);
	camera.render("../images/output.png");

	return 0;
}