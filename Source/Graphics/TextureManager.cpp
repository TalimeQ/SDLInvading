#include "TextureManager.h"
#include "SDL_image.h"


SDL_Texture* TextureManager::LoadTexture(const char* FileName, SDL_Renderer* Renderer)
{
    SDL_Surface* TempSurface = IMG_Load(FileName);
    SDL_Texture* Texture = SDL_CreateTextureFromSurface(Renderer, TempSurface);

    SDL_FreeSurface(TempSurface);

    return Texture;
}
