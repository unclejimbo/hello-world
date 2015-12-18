#include "Sprite.h"
#include "Texture.h"

Sprite::Sprite()
{
	_texture = nullptr;
	_position = { 0, 0 };
	_width = 0;
	_height = 0;
	_clip = { 0, 0, 0, 0 };
}

void Sprite::render(int x, int y)
{
	_position = { x, y };
	_texture->render(x, y, &_clip);
}