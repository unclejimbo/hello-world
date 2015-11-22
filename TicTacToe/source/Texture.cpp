#include "../include/Texture.h"

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>

void Texture::bind_renderer(SDL_Renderer* renderer)
{
	_renderer = renderer;
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

int Texture::get_width()
{
	return _width;
}

int Texture::get_height()
{
	return _height;
}