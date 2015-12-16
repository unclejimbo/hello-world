#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>

#include "../include/Texture.h"
#include "../include/Sprite.h"
#include "../include/Button.h"
#include "../include/Text.h"
#include "../include/Font.h"
#include "../include/Intro.h"

using namespace std;

// Window size
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

enum GameStates
{
	STATE_NULL,
	STATE_INTRO,
	STATE_MENU,
	STATE_PVP,
	STATE_PVC,
	STATE_EXIT
};

int main(int argc, char* argv[])
{
	// Engine Initializition
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cerr << "SDL couldn't initialize! SDL Error: " << SDL_GetError() << endl;
		return -1;
	}

	SDL_Window* window = SDL_CreateWindow("TicTacToe",
										  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
										  SCREEN_WIDTH, SCREEN_HEIGHT,
										  SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		cerr << "Window couldn't be created! SDL Error: " << SDL_GetError() << endl;
		return -1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		cerr << "Renderer couldn't be created! SDL Error " << SDL_GetError() << endl;
		return -1;
	} else {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	}

	int image_flag = IMG_INIT_JPG;
	if (!(IMG_Init(image_flag) & image_flag)) {
		cerr << "SDL_image couldn't initialize! SDL_image Error: " << IMG_GetError() << endl;
		return -1;
	}

	if (TTF_Init() == -1) {
		cerr << "SDL_ttf couldn't initialize! SDL_ttf Error: " << TTF_GetError() << endl;
		return -1;
	}

	// Creating resources	
	Intro* intro = new Intro(renderer);

	// Game loop
	bool quit = false;
	SDL_Event event;

	while (!quit) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT)
				quit = true;
		}

		intro->render();

		SDL_RenderPresent(renderer);
	}

	// Free resources
	delete intro;

	SDL_DestroyRenderer(renderer);
	renderer = nullptr;

	SDL_DestroyWindow(window);
	window = nullptr;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	return 0;
}