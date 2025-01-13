#include "Game.h"
#include <iostream>

SDL_Texture* PlayerText;
SDL_Rect SourceRect,DestRect;


Game::Game()
{

}

Game::~Game()
{
	Clean();
}

void Game::Initialize(const char* Title, int XPos, int YPos, int Width, int Height, bool Fullscreen)
{

	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		return;
	}

	std::cout << "SDL Initialized!" << std::endl;

	int WindowFlags = 0;
	if (Fullscreen)
	{
		WindowFlags = SDL_WINDOW_FULLSCREEN;
	}


	Window = SDL_CreateWindow(Title, XPos, YPos, Width, Height, WindowFlags);
	if (Window == nullptr)
	{
		return;
	}

	std::cout << "Window created!" << std::endl;

	Renderer = SDL_CreateRenderer(Window, -1, 0);
	if (Renderer == nullptr)
	{
		return;
	}

	SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
	std::cout << "Renderer Created!" << std::endl;

	bIsRunning = true;

	//SDL Image test TODO:: Remove
	SDL_Surface* TempSurface = IMG_Load("Assets/PlayerShip.png");
	PlayerText = SDL_CreateTextureFromSurface(Renderer, TempSurface);
	SDL_FreeSurface(TempSurface);

}

void Game::HandleEvents()
{
	SDL_Event Event;
	SDL_PollEvent(&Event);

	switch (Event.type)
	{
		case SDL_QUIT:
			bIsRunning = false;
			break;
		default:
			break;
	}
}

void Game::Update()
{
	Counter++;
	DestRect.h = 64;
	DestRect.w = 64;

	DestRect.x = Counter;
}

void Game::Clean()
{
	SDL_DestroyWindow(Window);
	SDL_DestroyRenderer(Renderer);
	SDL_Quit();

	std::cout << "Game Quit!" << std::endl;
}

void Game::Render()
{
	// Clear buffer
	SDL_RenderClear(Renderer);
	// Now we add stuff to render
	SDL_RenderCopy(Renderer, PlayerText,NULL,&DestRect);


	// This will display
	SDL_RenderPresent(Renderer);
}