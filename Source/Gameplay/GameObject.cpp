#include "GameObject.h"
#include "../Graphics/TextureManager.h"

GameObject::GameObject(const char* TextureSheet, SDL_Renderer* InRenderer, int32_t InitX, int32_t InitY)
{
	Renderer = InRenderer;
	ObjectTexture = TextureManager::LoadTexture(TextureSheet, Renderer);

	xPos = InitX;
	yPos = InitY;
}

GameObject::~GameObject()
{
}

void GameObject::Update(double DeltaTime)
{
	xPos++;
	yPos++;

	SourceRect.h = 32;
	SourceRect.w = 32;
	SourceRect.x = 0;
	SourceRect.y = 0;

	DestinationRect.h = SourceRect.h * 2;
	DestinationRect.w = SourceRect.w * 2;
	DestinationRect.x = xPos;
	DestinationRect.y = yPos;
}

void GameObject::Render()
{
	SDL_RenderCopy(Renderer, ObjectTexture, &SourceRect, &DestinationRect);
}
