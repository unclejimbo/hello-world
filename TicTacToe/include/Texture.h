#pragma once

#include <SDL.h>
#include <string>

class Texture
{
public:
	Texture() = default;
	~Texture() { free(); }

	bool load_from_file(std::string path);

	inline void free();

	// Render texture in position (x,y) with clip rectangle
	void render(int x, int y, SDL_Rect* clip = nullptr);

	inline int get_width();

	inline int get_height();

	inline void set_renderer(SDL_Renderer* renderer);

private:
	SDL_Texture* _texture = nullptr;
	SDL_Renderer* _renderer = nullptr;
	int _width, _height;
};