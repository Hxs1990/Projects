#include "flip.h"
#include <vector>

Flip::Flip(Image *i):
	ImageDecorator{i}{}

void Flip::render(PPM &ppm){
	pic->render(ppm); //render the other effects first
	int height = ppm.getHeight();
	int width = ppm.getWidth();
	std::vector<Pixel> pixels =  ppm.getPixels();
	std::vector<Pixel> newPixels;
	// Loops through the height and width to construct a new vector
	//  where the rows are flipped
	for (int h = 0; h < height; ++h){
		for (int w = 0; w < width; ++w){
			newPixels.emplace_back(pixels[(h*width)+(width-1-w)]);
		}
	}
	// Swap the newly created vector with the old one
	newPixels.swap(ppm.getPixels());
}

