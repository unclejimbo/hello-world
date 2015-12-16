#include "../include/Button.h"

Button::Button()
{
	_current_sprite = MOUSE_OUT;

	for (int i = 0; i < MOUSE_SUM; ++i) {
		_button_icons[i] = { 0, 0, 0, 0 };
	}

	_left_click = false;
}


Event Button::handle(SDL_Event* e)
{
	Event event = Event::NO_ACTION;

	if (e->type == SDL_MOUSEMOTION || 
		e->type == SDL_MOUSEBUTTONDOWN ||
		e->type == SDL_MOUSEBUTTONUP) {

		int x, y;
		SDL_GetMouseState(&x, &y);

		// Check if the cursor is inside the button area
		bool active = true;
		if (x < _position.x || y < _position.y ||
			x > _position.x + _width || y > _position.y + _height)
			active = false;

		if (!_left_click) {
			if (active) {
				if (e->type == SDL_MOUSEBUTTONDOWN && e->button.button == SDL_BUTTON_LEFT) {
					_current_sprite = MOUSE_DOWN;
					_left_click = true;
				} else {
					_current_sprite = MOUSE_OVER;
				}
			} else {
				_current_sprite = MOUSE_OUT;
			}
		} else {
			if (active) {
				if (e->type == SDL_MOUSEBUTTONUP && e->button.button == SDL_BUTTON_LEFT) {
					_current_sprite = MOUSE_OVER;
					_left_click = false;
					event = Event::LEFT_CLICK;
				} else {
					_current_sprite = MOUSE_DOWN;
				}
			} else {
				if (e->type == SDL_MOUSEBUTTONUP && e->button.button == SDL_BUTTON_LEFT) {
					_current_sprite = MOUSE_OUT;
					_left_click = false;
				} else {
					_current_sprite = MOUSE_DOWN;
				}
			}
		}
	}

	return event;
}

void Button::render(int x, int y)
{
	_clip = _button_icons[_current_sprite];
	Sprite::render(x, y);
}
