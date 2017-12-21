#include "flip.h"
#include <vector>

Flip::Flip(Image *i):
	ImageDecorator{i}{}

void Flip::render(PPM &ppm){
	int height = ppm.getHeight();
	int width = ppm.getWidth();
	std::vector<Pixel> pixels =  ppm.getPixels();

	std::vector<Pixel> newPixels;
	for (unsigned int h = 0; h < height; ++h){
		for (unsigned int w = 0; w < width; ++w){
			newPixels[h*height+w] = pixels[h*height+(width-1-w)];
		}
	}
	ppm.getPixels().swap(newPixels);
	render(pic);
}

