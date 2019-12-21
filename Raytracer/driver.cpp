#include <iostream>
#include <lodepng.h>

void writeImage(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height) {
	lodepng::encode(filename, image, width, height);
}

int main() {

	unsigned width = 512, height = 512;
	std::vector<unsigned char> image;
	image.resize(width * height * 4);
	for (unsigned y = 0; y < height; y++)
		for (unsigned x = 0; x < width; x++) {
			image[4 * width * y + 4 * x + 0] = 255 * !(x & y);
			image[4 * width * y + 4 * x + 1] = x | y;
			image[4 * width * y + 4 * x + 2] = x | y;
			image[4 * width * y + 4 * x + 3] = 255;
		}

	writeImage("../images/output.png", image, width, height);
}