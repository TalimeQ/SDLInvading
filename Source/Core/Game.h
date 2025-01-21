#pragma once
#include "SDL.h"
#include "SDL_image.h"

class InputHandler;

class Game {
	// Game Methods
public:
	Game();
	~Game();

	void Initialize(const char* Title, int XPos, int YPos, int Width, int Height, bool Fullscreen);
	
	void HandleEvents();
	void Update(double DeltaTime);
	void Render();

	// Cleanup memory for example
	void Clean();

	bool IsRunning() { return bIsRunning; }

	// Game Data
public:
	static SDL_Renderer* Renderer;

	static InputHandler* Input;
private:

	bool bIsRunning{false};

	Uint32 Counter{0};

	SDL_Window* Window{nullptr};

};