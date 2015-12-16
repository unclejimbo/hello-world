#pragma once

#include "../include/GameState.h"

class Intro : public GameState
{
public:
	Intro(SDL_Renderer* renderer);
	~Intro();

	Event handle(SDL_Event* e) override {}
	void logic() override {}
	void render() override;

private:
	Font* _font_title;
	Font* _font_decription;
	Text* _title;
	Text* _description;
};