#pragma once

struct SDL_Texture;
struct SDL_Renderer;

class TextureManager
{

public:
	static SDL_Texture* LoadTexture(const char* FileName, SDL_Renderer* Renderer);
};

