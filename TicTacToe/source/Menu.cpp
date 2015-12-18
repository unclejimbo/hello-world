#include "../include/Menu.h"

Menu::Menu(SDL_Renderer* renderer)
{
	_font_title = new Font();
	_font_title->open("../resource/fonts/AD.ttf", 36);

	_title = new Text("TicTacToe");
	_title->bind_font(_font_title);
	_title->bind_renderer(renderer);
	_title->create_texture();

	_tex_btns = new Texture();
	_tex_btns->bind_renderer(renderer);
	_tex_btns->load_from_file("../resource/images/menu_buttons.jpg");

	_pvc = new Button(); 
	_pvc->bind_texture(_tex_btns);
	_pvc->set_icon(0, 0, 200, 100, MOUSE_OUT);
	_pvc->set_icon(0, 100, 200, 100, MOUSE_OVER);
	_pvc->set_icon(0, 200, 200, 100, MOUSE_DOWN);

	_pvp = new Button();
	_pvp->bind_texture(_tex_btns);
	_pvp->set_icon(200, 0, 200, 100, MOUSE_OUT);
	_pvp->set_icon(200, 100, 200, 100, MOUSE_OVER);
	_pvp->set_icon(200, 200, 200, 100, MOUSE_DOWN);
}

Menu::~Menu()
{
	delete _font_title;
	delete _title;
	delete _tex_btns;
	delete _pvc;
	delete _pvp;

	_font_title = nullptr;
	_title = nullptr;
	_tex_btns = nullptr;
	_pvc = nullptr;
	_pvp = nullptr;
}

Event Menu::handle(SDL_Event* e)
{
	if (_pvp->handle(e) == Event::LEFT_CLICK) {
		return Event::PVP;
	}
	if (_pvc->handle(e) == Event::LEFT_CLICK) {
		return Event::PVC;
	}
}

void Menu::render()
{
	_title->render(300, 50);
	_pvc->render(300, 150);
	_pvp->render(300, 300);
}