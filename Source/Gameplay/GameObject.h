#pragma once
#include "../Core/Game.h"

class GameObject
{

public:
	GameObject(const char* TextureSheet, SDL_Renderer* InRenderer, int32_t InitX, int32_t InitY);
	~GameObject();

	void Update(double DeltaTime);
	void Render();

protected:

private:
	// TODO make it vector
	int32_t xPos;
	int32_t yPos;

	SDL_Texture* ObjectTexture;
	SDL_Rect SourceRect, DestinationRect;
	SDL_Renderer* Renderer;
};

