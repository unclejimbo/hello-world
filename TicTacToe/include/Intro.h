#pragma once

#include "GameState.h"

class Intro : public GameState
{
public:
	Intro(SDL_Renderer* renderer);
	~Intro();

	Event handle(SDL_Event* e) override { return Event::NO_ACTION; }
	void logic() override {}
	void render() override;

private:
	Font* _font_title;
	Font* _font_decription;
	Text* _title;
	Text* _description;
};