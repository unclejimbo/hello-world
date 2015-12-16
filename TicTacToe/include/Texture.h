#pragma once

#include <SDL.h>
#include <string>

class Texture
{
public:
	Texture();
	~Texture();

	bool load_from_file(std::string path);
	void free();

	void bind_renderer(SDL_Renderer* renderer);
	// Render texture in position (x,y) with clip rectangle
	void render(int x, int y, SDL_Rect* clip = nullptr);

	int get_width();
	int get_height();

	void set_color_key(int r, int g, int b);

protected:
	SDL_Texture* _texture;
	SDL_Renderer* _renderer;
	int _width, _height;
	SDL_Color _color_key;
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