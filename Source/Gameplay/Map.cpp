#include "Map.h"
#include "../Graphics/TextureManager.h"

// TODO:: Remove
int32_t Lvl1[20][25]
{ 
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,2,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

Map::Map()
{
	Dirt = TextureManager::LoadTexture("Assets/Dirt.png");
	Water = TextureManager::LoadTexture("Assets/Water.png");
	Grass = TextureManager::LoadTexture("Assets/Grass.png");	

	LoadMap(Lvl1);

	Source.x = 0;
	Source.y = 0;

	Destination.x = 0;
	Destination.y = 0;

	Source.w = Destination.w = 32;
	Source.h = Destination.h = 32;

}

Map::~Map()
{
}

void Map::LoadMap(int32_t inMapArray[20][25])
{
	for (int32_t row = 0; row < 20; row++)
	{
		for (int32_t column = 0; column < 25; column++)
		{
			MapArray[row][column] = inMapArray[row][column];
		}
	}
}

void Map::DrawMap()
{
	int32_t Type = 0;

	for (int32_t row = 0; row < 20; row++)
	{
		for (int32_t column = 0; column < 25; column++)
		{
			Type = MapArray[row][column];

			Destination.x = column * 32;
			Destination.y = row * 32;

			switch (Type)
			{
			case 0:
				SDL_RenderCopy(Game::Renderer,Water, &Source, &Destination);
				//TextureManager::Draw(Water, Source, Destination);
				break;
			case 1:
				TextureManager::Draw(Dirt, Source, Destination);
				break;
			case 2:
				TextureManager::Draw(Grass, Source, Destination);
				break;
			default:
				break;

			}
		}
	}
}
