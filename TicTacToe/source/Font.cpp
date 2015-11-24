#include "../include/Font.h"

#include <iostream>

Font::~Font()
{
	if (_font != nullptr) {
		TTF_CloseFont(_font);
		_font = nullptr;
	}
}

bool Font::open(std::string path, unsigned size)
{
	_size = size;
	_font = TTF_OpenFont(path.c_str(), _size);
	if (_font == nullptr) {
		std::cerr << "Couldn't open font " << path << std::endl
			<< "SDL_ttf Error: " << TTF_GetError() << std::endl;
		return false;
	}
	return true;
}