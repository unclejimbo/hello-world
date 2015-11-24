#pragma once

#include "Texture.h"
#include "Font.h"

#include <SDL_ttf.h>
#include <string>

class Text : public Texture
{
public:
	Text();
	Text(std::string text);
	~Text() { _font = nullptr; }

	bool create_texture();
	bool Text::create_texture(std::string text);

	std::string get_text();
	void set_text(std::string text);

	SDL_Color get_color();
	void set_color(SDL_Color color);
	void set_color(int r, int g, int b);

	Font* get_font();
	void bind_font(Font* font);

private:
	std::string _text;
	SDL_Color _color;
	Font* _font;
};

inline std::string Text::get_text()
{
	return _text;
}

inline void Text::set_text(std::string text)
{
	_text = text;
}

inline SDL_Color Text::get_color()
{
	return _color;
}

inline void Text::set_color(SDL_Color color)
{
	_color = color;
}

inline void Text::set_color(int r, int g, int b)
{
	_color = { r, g, b };
}

inline Font* Text::get_font()
{
	return _font;
}

inline void Text::bind_font(Font* font)
{
	_font = font;
}