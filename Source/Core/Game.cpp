#include "Game.h"
#include <iostream>
#include "../Graphics/TextureManager.h"
#include "Input/InputHandler.h"
#include "ECS/ECS.h"
#include "../Gameplay/Components/PositionComponent.h"


// TODO :: Try to make them smorter
SDL_Renderer* Game::Renderer{ nullptr };
InputHandler* Game::Input{ nullptr };

Scene CurrentScene;


//EntityManager Game::EntityManager;

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

	// Other Initializations
	Input = new InputHandler();

	bIsRunning = true;

/*	EntityID PlayerEnt = CurrentScene.NewEntity();
	CurrentScene.Assign<TransformComponent>(PlayerEnt)*/;
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

	Input->ParseKeyboard(&Event);

}

void Game::Update(double DeltaTime)
{
	//Manager.Update(DeltaTime);
}

void Game::Clean()
{
	SDL_DestroyWindow(Window);
	SDL_DestroyRenderer(Renderer);
	SDL_Quit();

	delete(Input);

	std::cout << "Game Quit!" << std::endl;
}

void Game::Render()
{
	// Clear buffer
	SDL_RenderClear(Renderer);
	// Now we add stuff to render
	//Manager.Draw();


	// This will display
	SDL_RenderPresent(Renderer);
}