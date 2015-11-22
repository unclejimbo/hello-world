#pragma once

#include <SDL.h>

#include "Texture.h"

class Sprite
{
public:
	Sprite();
	~Sprite();

	inline void bind_texture(Texture* tex);
	inline Texture* get_texture();

	inline void set_clip_rect(int x, int y, int width, int height);
	inline void set_clip_rect(SDL_Rect source_rect);
	inline SDL_Rect get_clip_rect();

	inline void render(int x, int y);

private:
	Texture* _texture;

	SDL_Rect _clip;
};