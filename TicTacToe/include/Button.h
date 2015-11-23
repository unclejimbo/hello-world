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

	inline void set_icon(int x, int y, int width, int height, MouseStates s);
	inline void set_icon(SDL_Rect clip, MouseStates s);

	void handle(SDL_Event* e);

	inline void render(int x, int y);

private:
	MouseStates _current_sprite;
	SDL_Rect _button_icons[MOUSE_SUM];
};