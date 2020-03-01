#include <lodepng.h>
#include "../header/image.h"

Image::Image(const unsigned width = 256, const unsigned height = 256) {
	this->width = width;
	this->height = height;
	this->contents = std::vector<unsigned char>(width * height * 4);
}

void Image::setPixel(const unsigned x, const unsigned y, const glm::ivec4 color) {
	contents[4 * width * y + 4 * x + 0] = color.r;
	contents[4 * width * y + 4 * x + 1] = color.g;
	contents[4 * width * y + 4 * x + 2] = color.b;
	contents[4 * width * y + 4 * x + 3] = color.a;
}

void Image::write(const std::string filename) {
	lodepng::encode(filename, contents, width, height);
}