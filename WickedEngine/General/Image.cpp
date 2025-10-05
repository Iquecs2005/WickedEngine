#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <iostream>

Image::Image(const std::string& fileName)
{
	stbi_set_flip_vertically_on_load(true);
	imageData = stbi_load(fileName.c_str(), &width, &height, &nChannels, 0);
	if (!imageData) 
	{
		std::cerr << "Could not load image file: " << fileName << std::endl;
	}
}

ImagePtr Image::Make(const std::string& fileName)
{
	return ImagePtr(new Image(fileName));
}