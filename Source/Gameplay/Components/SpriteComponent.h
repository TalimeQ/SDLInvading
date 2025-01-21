#pragma once
#include "../../Core/ECS.h"
#include "PositionComponent.h"
#include "SDL.h"
#include "../../Graphics/TextureManager.h"

class SpriteComponent : public Component
{

public:
	SpriteComponent() = default;
	SpriteComponent(const char* TexturePath)
	{
		SetTexture(TexturePath);
	}

	// Component Overrides
	void Init() override
	{
		Position = &OwnerEntity->GetComponent<PositionComponent>();

		SrcRect.x = SrcRect.y = 0;
		SrcRect.w = SrcRect.h = 32;
		DestRect.w = DestRect.h = 32;
	}

	void Update(double DeltaTime) override
	{
		DestRect.x = Position->X();
		DestRect.y = Position->Y();

	}

	void Draw() override
	{
		TextureManager::Draw(Texture, SrcRect, DestRect);
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
	PositionComponent* Position{ nullptr };
	SDL_Texture* Texture{ nullptr };
	SDL_Rect SrcRect, DestRect;
};

