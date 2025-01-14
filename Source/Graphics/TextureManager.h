#pragma once

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

class TextureManager
{

public:
	static SDL_Texture* LoadTexture(const char* FileName);
	static void Draw(SDL_Texture* Texture, SDL_Rect& Source, SDL_Rect& Destination);
};

