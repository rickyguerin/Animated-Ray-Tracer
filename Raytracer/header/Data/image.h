#pragma once
#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <vector>
#include <glm/vec3.hpp>

class Image {
private:
	// Image dimensions
	unsigned width;
	unsigned height;

	// Image pixel colors
	std::vector<unsigned char> contents;

public:
	// Constructor
	Image(const unsigned width, const unsigned height);

	// Set the color of one pixel in the Image
	void setPixel(const unsigned x, const unsigned y, const glm::vec3& color);

	// Write the contents of this Image to a file
	void write(const std::string& filename) const;
};

#endif