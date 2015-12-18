#pragma once

#include "GameState.h"

#include "Button.h"

class Menu : public GameState
{
public:
	Menu(SDL_Renderer* renderer);
	~Menu();

	Event handle(SDL_Event* e) override;
	void logic() override {}
	void render() override;
private:
	Font* _font_title;
	Text* _title;
	Texture* _tex_btns;
	Button* _pvc;
	Button* _pvp;
};