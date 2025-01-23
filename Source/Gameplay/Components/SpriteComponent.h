#pragma once
#include "SDL.h"
#include "../../Graphics/TextureManager.h"

class SpriteComponent 
{

public:
	SpriteComponent()
	{
		SrcRect.x = SrcRect.y = 0;
		SrcRect.w = SrcRect.h = 32;
		DestRect.w = DestRect.h = 32;
	}

	SpriteComponent(const char* TexturePath) : SpriteComponent()
	{
		SetTexture(TexturePath);
	}

	//Sprite Component methods
	void SetTexture(const char* TexturePath)
	{
		FreeTexture();
		Texture = TextureManager::LoadTexture(TexturePath);
	}

	void FreeTexture()
	{
		if (Texture != nullptr)
		{
			SDL_DestroyTexture(Texture);
			Texture = nullptr;
		}
	}


	// Sprite Component Data
private:
	//PositionComponent* Position{ nullptr };
	SDL_Texture* Texture{ nullptr };
	SDL_Rect SrcRect, DestRect;
};

