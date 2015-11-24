#pragma once

#include <SDL_ttf.h>

#include <string>

class Font
{
public:
	Font() = default;
	~Font();

	TTF_Font* get_font();
	bool open(std::string path, unsigned size = 24);

	unsigned get_size();
private:
	TTF_Font* _font = nullptr;
	unsigned _size = 24;
};

inline TTF_Font* Font::get_font()
{
	return _font;
}

inline unsigned Font::get_size()
{
	return _size;
}
