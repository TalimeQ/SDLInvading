#include "ResourceManager.h"
#include <SDL_image.h>


ResourceManager::ResourceManager()
{

}

ResourceManager::ResourceManager(ResourceManager const&)
{

}

ResourceManager ResourceManager::operator=(ResourceManager const& rhs)
{
	return *this;
}

ResourceManager& ResourceManager::GetInstance()
{
	static ResourceManager* Instance = new ResourceManager;

	return *Instance;
}

SDL_Surface* ResourceManager::GetSurface(std::string FilePath)
{
	auto Search = Surfaces.find(FilePath);

	if (Search != Surfaces.end())
	{
		return Surfaces[FilePath];
	}

	// Potentially wrap this so that we free resources after not using them for a while
	// A shared pointer for example? Then free it after X time passes?
	SDL_Surface* CreatedSurface = IMG_Load(FilePath.c_str());
	Surfaces.emplace(std::make_pair(FilePath, CreatedSurface));

	return CreatedSurface;
}
