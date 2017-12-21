#include "rotate.h"
#include <vector>

Rotate::Rotate(Image *i):
	ImageDecorator{i}{}

void Rotate::render(PPM &ppm){
	int height = ppm.getHeight();
	int width = ppm.getWidth();
	std::vector<Pixel> pixels =  ppm.getPixels();

	std::vector<Pixel> newPixels;
	for (unsigned int h = 0; h < height; ++h){
		for (unsigned int w = 0; w < width; ++w){
			newPixels[h*height+w] = pixels[width*(height-w-1)+h];
		}
	}
	ppm.getHeight() = width;
	ppm.getWidth() = height;
	ppm.getPixels().swap(newPixels);
	render(pic);
}