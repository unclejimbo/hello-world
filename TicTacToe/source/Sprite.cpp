#include "../include/Sprite.h"
#include "../include/Texture.h"

Sprite::Sprite()
{
	_texture = nullptr;
	_clip = { 0, 0, 0, 0 };
}

Sprite::~Sprite()
{
	if (_texture != nullptr) {
		_texture = nullptr;
	}
}

void Sprite::bind_texture(Texture* tex)
{
	_texture = tex;
}

Texture* Sprite::get_texture()
{
	return _texture;
}

void Sprite::set_clip_rect(int x, int y, int width, int height)
{
	_clip = { x, y, width, height };
}

void Sprite::set_clip_rect(SDL_Rect source_rect)
{
	_clip = source_rect;
}

SDL_Rect Sprite::get_clip_rect()
{
	return _clip;
}

void Sprite::render(int x, int y)
{
	_texture->render(x, y, &_clip);
}