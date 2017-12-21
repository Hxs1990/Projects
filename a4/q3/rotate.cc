#include "rotate.h"
#include <vector>


Rotate::Rotate(Image *i):
	ImageDecorator{i}{}

void Rotate::render(PPM &ppm){
	pic->render(ppm); // render the other effects first
	int height = ppm.getHeight();
	int width = ppm.getWidth();
	std::vector<Pixel> pixels = ppm.getPixels();
	// loop through the heigh and the widths of the new vector and
	//  construct a rotation 90 degrees CW
	std::vector<Pixel> newPixels(pixels.size());
	for (int h = 0; h < height; ++h){
		for (int w = 0; w < width; ++w){
			newPixels[w*height + h] = (pixels[width*(height-h-1)+w]);
		}
	}
	// Swap the width with the height and the old vector with the new vector
	ppm.getHeight() = width;
	ppm.getWidth() = height;
	ppm.getPixels().swap(newPixels);
}


