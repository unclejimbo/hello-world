#include "../include//Button.h"

#include <iostream>

Button::Button()
{
	_current_sprite = MOUSE_OUT;

	for (int i = 0; i < MOUSE_SUM; ++i) {
		_button_icons[i] = { 0, 0, 0, 0 };
	}
}

void Button::set_icon(int x, int y, int width, int height, MouseStates s)
{
	_button_icons[s] = { x, y, width, height };
}

void Button::set_icon(SDL_Rect clip, MouseStates s)
{
	_button_icons[s] = clip;
}

void Button::handle(SDL_Event* e)
{
	if (e->type == SDL_MOUSEMOTION || 
		e->type == SDL_MOUSEBUTTONDOWN ||
		e->type == SDL_MOUSEBUTTONUP) {

		int x, y;
		SDL_GetMouseState(&x, &y);

		// Check if the cursor is inside the button area
		bool active = true;
		if (x < get_position().x || y < get_position().y ||
			x > get_position().x + get_width() || y > get_position().y + get_height())
			active = false;

		if (active) {
			switch (e->type) {
			case SDL_MOUSEMOTION:
				_current_sprite = MOUSE_OVER;
				break;
			case SDL_MOUSEBUTTONDOWN:
				_current_sprite = MOUSE_DOWN;
				break;
			case SDL_MOUSEBUTTONUP:
				_current_sprite = MOUSE_UP;
				break;
			default:
				_current_sprite = MOUSE_OUT;
				break;
			}
		}
	}
}

void Button::render(int x, int y)
{
	get_texture()->render(x, y, &_button_icons[_current_sprite]);
}
