#include "../include/Intro.h"

Intro::Intro(SDL_Renderer* renderer)
{
	_font_title = new Font();
	_font_title->open("../../resource/fonts/AD.ttf", 36);

	_font_decription = new Font();
	_font_decription->open("../../resource/fonts/AD.ttf", 24);

	_title = new Text("TicTacToe");
	_title->bind_font(_font_title);
	_title->bind_renderer(renderer);
	_title->create_texture();

	_description = new Text("Made by unclejimbo");
	_description->bind_font(_font_decription);
	_description->bind_renderer(renderer);
	_description->create_texture();
}

Intro::~Intro()
{
	delete _font_title;
	delete _font_decription;
	delete _title;
	delete _description;

	_font_title = nullptr;
	_font_decription = nullptr;
	_title = nullptr;
	_description = nullptr;
}

void Intro::render()
{
	_title->render(300, 200);
	_description->render(300, 300);
}