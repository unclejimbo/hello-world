#include "../include/Text.h"

#include <iostream>
#include <SDL.h>

Text::Text()
{
	_color.r = 0;
	_color.g = 0;
	_color.b = 0;
	_text = std::string();
	_font = nullptr;
}

Text::Text(std::string text) : _text(text)
{
	_color.r = 0;
	_color.g = 0;
	_color.b = 0;
	_font = nullptr;
}

bool Text::create_texture(std::string text)
{
	free();

	SDL_Surface* text_surface = TTF_RenderText_Solid(_font->get_font(), text.c_str(), _color);
	if (text_surface == nullptr) {
		std::cerr << "Unable to create text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
		return false;
	}

	_texture = SDL_CreateTextureFromSurface(_renderer, text_surface);
	if (_texture == nullptr) {
		std::cerr << "Unable to create texture from text! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	_width = text_surface->w;
	_height = text_surface->h;
	_text = text;

	SDL_FreeSurface(text_surface);

	return true;
}

bool Text::create_texture()
{
	free();

	SDL_Surface* text_surface = TTF_RenderText_Solid(_font->get_font(), _text.c_str(), _color);
	if (text_surface == nullptr) {
		std::cerr << "Unable to create text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
		return false;
	}

	_texture = SDL_CreateTextureFromSurface(_renderer, text_surface);
	if (_texture == nullptr) {
		std::cerr << "Unable to create texture from text! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	_width = text_surface->w;
	_height = text_surface->h;

	SDL_FreeSurface(text_surface);

	return true;
}