#include "sepia.h"

#include <iostream>

Sepia::Sepia(Image *i):
	ImageDecorator{i}{};

void Sepia::render(PPM &ppm){
	pic->render(ppm); // render the other effects first;
	// Loop through every single pixel in the vector and
	//  update its red, green, and blue values.
	for(auto &p: ppm.getPixels()){
		unsigned int newRed = p.r * .393 + p.g * .769 + p.b * .189;
		unsigned int newGreen = p.r * .349 + p.g * .686 + p.b * .168;
		unsigned int newBlue = p.r * .272 + p.g * .534 + p.b * .131;
		if (newRed > 255) newRed = 255;
		if (newGreen > 255) newGreen = 255;
		if (newBlue > 255) newBlue = 255;
		Pixel np{newRed,newGreen,newBlue};
		p = np; 
	}
}

