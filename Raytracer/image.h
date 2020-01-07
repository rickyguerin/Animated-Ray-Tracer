#pragma once
#ifndef IMAGE_H
#define IMAGE_H

#include <vector>

class Image {
private:
	unsigned width;
	unsigned height;
	std::vector<unsigned char> contents;

public:
	Image(unsigned width, unsigned height);

	unsigned getWidth();

	unsigned getHeight();

	void setPixel(long long x, long long y, unsigned char r, unsigned char g, unsigned char b, unsigned char a);

	void write(const char* filename);
};

#endif