#include "SDL.h"
#include "Core/Game.h"


int main(int agrc, char* argv[])
{
	Game GameInstance{};

	GameInstance.Initialize("Invading Forces 4", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

	while (GameInstance.IsRunning())
	{
		GameInstance.HandleEvents();
		GameInstance.Update();
		GameInstance.Render();
	}

	return 0;
}