#include <stdlib.h>
#include <stdio.h>
#include "SDL\include\SDL.h"
#include "SDL_image\include\SDL_image.h"

#pragma comment( lib, "SDL/libx86/SDL2.lib")
#pragma comment( lib, "SDL/libx86/SDL2main.lib")

#pragma comment( lib, "SDL_image/libx86/SDL2_image")

#define MAX_BULLET_AMOUNT 10

int main(int argc, char* argv[])
{
	IMG_INIT_PNG;
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window *window;
	SDL_Renderer *renderer;

	window = SDL_CreateWindow("MyWindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

	SDL_Surface* protoShip = IMG_Load("images/player.png");
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

	SDL_Rect srcRect;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = 24;
	srcRect.h = 24;

	SDL_Rect protoShipRect;
	protoShipRect.x = 279;
	protoShipRect.y = 190;
	protoShipRect.w = 96;
	protoShipRect.h = 96;


	SDL_Rect beamRect;
	beamRect.x = 641;
	beamRect.y = 481;
	beamRect.h = 16;
	beamRect.w = 16;

	bool up = false;
	bool down = false;
	bool right = false;
	bool left = false;
	bool space = false;
	bool escape = false;
	bool isshotfired = false;
	int framecounterup = 0, framecounterdown = 0;

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
		srcRect.x = 0;
		if (left)
		{
			if (protoShipRect.x >= 0)
				protoShipRect.x -= 10;
		}

		if (right)
		{
			if (protoShipRect.x <= 530)
			protoShipRect.x += 10;
		}

		if (up)
		{
			if (protoShipRect.y >= 10)
			{
				protoShipRect.y -= 10;
				framecounterup++;
			}
			srcRect.x = 24;
			if (framecounterup == 20)
			{
				srcRect.x = 48;
			}
		}

		if (down)
		{
			if (protoShipRect.y <= 400)
			{
				protoShipRect.y += 10;
				framecounterdown++;
			}
			srcRect.x = 72;
			if (framecounterdown == 20)
			{
				srcRect.x = 96;
			}
		}

		if (space)
		{
			if (!isshotfired)
			{
				beamRect.x = protoShipRect.x;
				beamRect.y = protoShipRect.y + 42;
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

		background_1.x -= 20;
		background_2.x -= 20;

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
		SDL_RenderCopy(renderer, protoShipTexture, &srcRect, &protoShipRect);
		SDL_RenderPresent(renderer);

	}

	IMG_Quit();
	SDL_Quit();
	return(0);
}