#pragma once
#include "../Core/Game.h"

class Map
{

public:
	Map();
	~Map();

	void LoadMap(int32_t InMapArray[20][25]);
	void DrawMap();

private:

	SDL_Rect Source, Destination;
	// Change to STD::VECTOR
	SDL_Texture* Dirt;
	SDL_Texture* Grass;
	SDL_Texture* Water;

	int32_t MapArray[20][25];
};

