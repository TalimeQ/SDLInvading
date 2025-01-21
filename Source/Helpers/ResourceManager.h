#pragma once
#include "SDL.h"
#include <string>
#include <unordered_map>

class ResourceManager
{

private:
	ResourceManager();
	ResourceManager(ResourceManager const&);
	ResourceManager operator=(ResourceManager const&);

public:
	static ResourceManager& GetInstance();

	SDL_Surface* GetSurface(std::string FilePath);


private:
	std::unordered_map<std::string, SDL_Surface*> Surfaces;
};

