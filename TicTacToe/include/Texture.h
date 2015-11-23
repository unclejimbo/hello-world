#pragma once

#include <SDL.h>
#include <string>

class Texture
{
public:
	Texture() = default;
	~Texture();

	bool load_from_file(std::string path);
	void free();

	void bind_renderer(SDL_Renderer* renderer);
	// Render texture in position (x,y) with clip rectangle
	void render(int x, int y, SDL_Rect* clip = nullptr);

	int get_width();
	int get_height();

private:
	SDL_Texture* _texture = nullptr;
	SDL_Renderer* _renderer = nullptr;
	int _width, _height;
};

inline void Texture::bind_renderer(SDL_Renderer* renderer)
{
	_renderer = renderer;
}

inline int Texture::get_width()
{
	return _width;
}

inline int Texture::get_height()
{
	return _height;
}