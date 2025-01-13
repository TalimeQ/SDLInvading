#pragma once
#include "SDL.h"
#include "SDL_image.h"

class Game {

public:
	Game();
	~Game();

	void Initialize(const char* Title, int XPos, int YPos, int Width, int Height, bool Fullscreen);
	
	void HandleEvents();
	void Update();
	void Render();

	// Cleanup memory for example
	void Clean();

	bool IsRunning() { return bIsRunning; }

private:

	bool bIsRunning{false};

	int32_t Counter{ 0 };

	SDL_Window* Window{nullptr};
	SDL_Renderer* Renderer{nullptr};
};