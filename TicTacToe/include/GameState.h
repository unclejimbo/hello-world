#pragma once

#include <SDL.h>
#include "Text.h"
#include "Sprite.h"
#include "Event.h"

static unsigned g_idx = 0;

class GameState
{
public:
	GameState() { _idx = g_idx++; }
	~GameState() = default;

	unsigned get_idx() { return _idx; }

	virtual Event handle(SDL_Event* e) = 0;
	virtual void logic() = 0; 
	virtual void render() = 0;

protected:
	unsigned _idx;
};