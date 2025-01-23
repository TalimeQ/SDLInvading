#pragma once
#include "SDL.h"

constexpr uint16_t MAX_ENTITIES = SDL_MAX_UINT16;

// We will move it to .cpp if it gets bigger. No need now
// Basic pool for components
struct ComponentPool
{
	ComponentPool(size_t InElementSize)
	{
		ElementSize = InElementSize;
		PoolData = new char[ElementSize * MAX_ENTITIES];
	}

	~ComponentPool()
	{
		delete[] PoolData;
	}

	inline void* Get(size_t Index)
	{
		return PoolData + Index * ElementSize;
	}

	char* PoolData{ nullptr };
	size_t ElementSize{ 0 };
};