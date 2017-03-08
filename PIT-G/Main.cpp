#include <stdlib.h>
#include <stdio.h>
#include "SDL/include/SDL.h"

#pragma comment( lib, "SDL/libx86/SDL2.lib")
#pragma comment( lib, "SDL/libx86/SDL2main.lib")

#define MAX_BULLET_AMOUNT 10

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window *window;
	SDL_Renderer *renderer;

	window = SDL_CreateWindow("MyWindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

	SDL_Surface* protoShip = SDL_LoadBMP("images/ProtoShip.bmp");
	SDL_Texture* protoShipTexture = SDL_CreateTextureFromSurface(renderer, protoShip);

	SDL_Surface* beam = SDL_LoadBMP("images/beam.bmp");
	SDL_Texture* beamTexture = SDL_CreateTextureFromSurface(renderer, beam);

	SDL_Surface* background = SDL_LoadBMP("images/background.bmp");
	SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, background);


	SDL_Rect background_1;
	background_1.h = 480;
	background_1.w = 820;
	background_1.x = 0;
	background_1.y = 0;

	SDL_Rect background_2;
	background_2.h = 480;
	background_2.w = 820;
	background_2.x = 820;
	background_2.y = 0;

	SDL_Rect protoShipRect;
	protoShipRect.x = 279;
	protoShipRect.y = 190;
	protoShipRect.w = 100;
	protoShipRect.h = 50;


	SDL_Rect beamRect;
	beamRect.x = 641;
	beamRect.y = 481;
	beamRect.h = 32;
	beamRect.w = 32;

	bool up = false;
	bool down = false;
	bool right = false;
	bool left = false;
	bool space = false;
	bool escape = false;
	bool isshotfired = false;

	bool exit = false;

	while (!exit)
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYUP)
			{
				switch (event.key.keysym.scancode)
				{
				case SDL_SCANCODE_LEFT:		left = false;		break;
				case SDL_SCANCODE_RIGHT:	right = false;		break;
				case SDL_SCANCODE_UP:		up = false;			break;
				case SDL_SCANCODE_DOWN:		down = false;		break;
				case SDL_SCANCODE_SPACE:	space = false;		break;
				}
			}

			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.scancode)
				{
				case SDL_SCANCODE_ESCAPE:	escape = true;		break;
				case SDL_SCANCODE_LEFT:		left = true;		break;
				case SDL_SCANCODE_RIGHT:	right = true;		break;
				case SDL_SCANCODE_UP:		up = true;			break;
				case SDL_SCANCODE_DOWN:		down = true;		break;
				case SDL_SCANCODE_SPACE:	space = true;		break;
				}
			}

		}
		if (left)
		{
			if (protoShipRect.x >= 0)
				protoShipRect.x -= 10;
		}

		if (right)
		{
			if (protoShipRect.x <= 540)
			protoShipRect.x += 10;
		}

		if (up)
		{
			protoShipRect.y -= 10;
		}

		if (down)
		{
			protoShipRect.y += 10;
		}

		if (space)
		{
			if (!isshotfired)
			{
				beamRect.x = protoShipRect.x;
				beamRect.y = protoShipRect.y + 18;
				isshotfired = true;
			}
		}
		if (isshotfired)
		{
			beamRect.x += 30;
		}
		if (beamRect.x >= 640)
		{
			isshotfired = false;
		}

		background_1.x -= 5;
		background_2.x -= 5;

		if (background_1.x <= -820)
		{
			background_1.x = 820;
		}

		if (background_2.x <= -820)
		{
			background_2.x = 820;
		}

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, backgroundTexture, NULL, &background_1);
		SDL_RenderCopy(renderer, backgroundTexture, NULL, &background_2);
		SDL_RenderCopy(renderer, beamTexture, NULL, &beamRect);
		SDL_RenderCopy(renderer, protoShipTexture, NULL, &protoShipRect);
		SDL_RenderPresent(renderer);

	}


	SDL_Quit();
	return(0);
}