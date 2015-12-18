#include "Texture.h"

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>

Texture::Texture()
{
	_color_key.r = 0;
	_color_key.g = 0;
	_color_key.b = 0;
	_texture = nullptr;
	_renderer = nullptr;
	_width = 0;
	_height = 0;
}

Texture::~Texture()
{
	free();
	_renderer = nullptr;
}

bool Texture::load_from_file(std::string path)
{
	// Get rid of the preexisting texture
	free();

	SDL_Surface* image = IMG_Load(path.c_str());
	if (image == nullptr) {
		std::cerr << "Unable to load image " << path
			<< " SDL_image Error: " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, _color_key.r, _color_key.g, _color_key.b));

	_texture = SDL_CreateTextureFromSurface(_renderer, image);
	if (_texture == nullptr) {
		std::cerr << "Unable to create texture from image " << path
			<< " SDL_image Error: " << IMG_GetError() << std::endl;
		return false;
	}

	_width = image->w;
	_height = image->h;

	SDL_FreeSurface(image);
	
	return true;
}

void Texture::free()
{
	if (_texture != nullptr) {
		SDL_DestroyTexture(_texture);
		_texture = nullptr;
		_width = 0;
		_height = 0;
	}
}

void Texture::render(int x, int y, SDL_Rect* clip /* = nullptr */)
{
	SDL_Rect render_rect = { x, y, _width, _height };

	if (clip != nullptr) {
		render_rect.w = clip->w;
		render_rect.h = clip->h;
	}

	SDL_RenderCopy(_renderer, _texture, clip, &render_rect);
}

void Texture::set_color_key(int r, int g, int b)
{
	_color_key.r = r;
	_color_key.g = g;
	_color_key.b = b;
}