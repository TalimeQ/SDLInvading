#include "TextureManager.h"
#include "SDL_image.h"
#include "../Core/Game.h"
#include "../Helpers/ResourceManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* FileName)
{

    SDL_Surface* TempSurface = ResourceManager::GetInstance().GetSurface(FileName);
    SDL_Texture* Texture = SDL_CreateTextureFromSurface(Game::Renderer, TempSurface);

    return Texture;
}

void TextureManager::Draw(SDL_Texture* Texture, SDL_Rect& Source, SDL_Rect& Destination)
{
    SDL_RenderCopy(Game::Renderer,Texture, &Source, &Destination);
}
