#pragma once

#include "LTexture.h"
#include "ScreenConsts.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <stdio.h>


class LMenu
{
public:
	LMenu(SDL_Renderer* gRenderer);

	~LMenu(void);

	void run();

	void update(SDL_Event e);

	void render();

	int isFinished();

	bool setFont();

	TTF_Font* font;

private:

	int position;

	int choice;

	bool ready;

	LTexture bgTex;
	LTexture pacman;

	LTexture start;
	SDL_Rect startRect;

	LTexture exit;
	SDL_Rect exitRect;

	LTexture arrow;
	SDL_Rect arrowRect;

	SDL_Renderer* gRenderer;

};

