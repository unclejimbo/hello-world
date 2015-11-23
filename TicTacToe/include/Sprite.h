#pragma once

#include <SDL.h>

#include "Texture.h"

class Sprite
{
public:
	Sprite();
	~Sprite()
	{
		_texture = nullptr;
	}

	void bind_texture(Texture* tex);
	Texture* get_texture();

	void set_clip_rect(int x, int y, int width, int height);
	void set_clip_rect(SDL_Rect source_rect);
	SDL_Rect get_clip_rect();

	SDL_Point get_position();
	int get_width();
	int get_height();

	virtual void render(int x, int y);

protected:
	SDL_Point _position;
	int _width, _height;
	SDL_Rect _clip;
	Texture* _texture;
};


inline void Sprite::bind_texture(Texture* tex)
{
	_texture = tex;
}

inline Texture* Sprite::get_texture()
{
	return _texture;
}

inline void Sprite::set_clip_rect(int x, int y, int width, int height)
{
	_clip = { x, y, width, height };
	_width = width;
	_height = height;
}

inline void Sprite::set_clip_rect(SDL_Rect source_rect)
{
	_clip = source_rect;
}

inline SDL_Rect Sprite::get_clip_rect()
{
	return _clip;
}

inline SDL_Point Sprite::get_position()
{
	return _position;
}

inline int Sprite::get_width()
{
	return _width;
}

inline int Sprite::get_height()
{
	return _height;
}
