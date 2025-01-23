#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include "ComponentPool.h"

// Global Definiitions

extern uint16_t GlobalComponentCounter;
constexpr uint16_t MAX_COMPONENTS = 32;

typedef std::bitset<MAX_COMPONENTS> ComponentMask;
typedef uint64_t EntityID;
typedef uint32_t EntityIndex;
typedef uint32_t EntityVersion;

template <class T>
uint16_t GetComponentTypeID()
{
	static uint16_t ComponentTypeId = GlobalComponentCounter++;
	return ComponentTypeId;
}

namespace Entity 
{
	inline EntityID CreateEntityID(EntityIndex Index, EntityVersion Version)
	{
		return ((EntityID)Index << 32) | ((EntityID)Version);
	}

	inline EntityIndex GetEntityIndex(EntityID ID)
	{
		return ID >> 32;
	}

	inline EntityVersion GetEntityVersion(EntityID ID)
	{
		return (EntityVersion)ID;
	}

	inline bool IsEntityValid(EntityID ID)
	{
		return (ID >> 32 != EntityIndex(-1));
	}

	#define INVALID_ENTITY CreateEntityId(EntityIndex(-1), 0)
}


struct Scene
{
	struct EntityDesc
	{
		EntityID ID;
		ComponentMask Mask;
	};

	std::vector<EntityDesc> Entities;
	std::vector<EntityIndex> FreeEntities;
	std::vector<ComponentPool> ComponentPools;

	EntityID NewEntity();

	void DestroyEntity(EntityID EntityID);

	template<typename T>
	T GetComponentFromEntity(EntityID EntityID);

	template<typename T>
	T Assign(EntityID ID);

	template<typename T>
	void Remove(EntityID ID);
};

