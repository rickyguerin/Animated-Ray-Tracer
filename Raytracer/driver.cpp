#include <lodepng.h>
#include "image.cpp"

int main() {
	Image image(512, 512);
	
	image.render("../images/empty.png");

	for (unsigned y = 0; y < image.getHeight(); y++) {
		for (unsigned x = 0; x < image.getWidth(); x++) {
			image.setPixel(x, y, 255 * !(x & y), x | y, x | y, 255);
		}
	}

	image.render("../images/output.png");

	return 0;
}