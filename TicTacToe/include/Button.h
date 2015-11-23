#pragma  once

#include <SDL.h>

#include "Sprite.h"

enum MouseStates
{
	MOUSE_OUT,
	MOUSE_OVER,
	MOUSE_DOWN,
	MOUSE_UP,
	MOUSE_SUM
};

class Button : public Sprite
{
public:
	Button();
	~Button() = default;

	void set_icon(int x, int y, int width, int height, MouseStates s);
	void set_icon(SDL_Rect clip, MouseStates s);

	void handle(SDL_Event* e);

	void render(int x, int y) override;

private:
	MouseStates _current_sprite;
	SDL_Rect _button_icons[MOUSE_SUM];
	bool _left_click;
};

inline void Button::set_icon(int x, int y, int width, int height, MouseStates s)
{
	_button_icons[s] = { x, y, width, height };
	_width = width;
	_height = height;
}

inline void Button::set_icon(SDL_Rect clip, MouseStates s)
{
	_button_icons[s] = clip;
	_width = clip.w;
	_height = clip.h;
}