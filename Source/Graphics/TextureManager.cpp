#include "TextureManager.h"
#include "SDL_image.h"
#include "../Core/Game.h"


SDL_Texture* TextureManager::LoadTexture(const char* FileName)
{

    SDL_Surface* TempSurface = IMG_Load(FileName);
    SDL_Texture* Texture = SDL_CreateTextureFromSurface(Game::Renderer, TempSurface);

    SDL_FreeSurface(TempSurface);

    return Texture;
}

void TextureManager::Draw(SDL_Texture* Texture, SDL_Rect& Source, SDL_Rect& Destination)
{
    SDL_RenderCopy(Game::Renderer,Texture, &Source, &Destination);
}
