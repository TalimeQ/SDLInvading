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
	std::vector<ComponentPool*> ComponentPools;

	EntityID NewEntity();

	void DestroyEntity(EntityID EntityID);

	template<typename T>
	T* GetComponentFromEntity(EntityID EntityID)
	{
		EntityIndex Index = Entity::GetEntityIndex(EntityID);
		if (Entities[Index].ID != EntityID)
		{
			return nullptr;
		}

		uint16_t ComponentID = GetComponentTypeID<T>();
		if (Entities[ComponentID].Mask.test(ComponentID))
		{
			return nullptr;
		}

		T* RequestedComponent = static_cast<T*>(ComponentPools[ComponentID]->Get(Index));
		return RequestedComponent;
	}


	template<typename T>
	T* Assign(EntityID EntityID)
	{
		// Checkup if entity is valid
		EntityIndex Index = Entity::GetEntityIndex(EntityID);
		if (Entities[Index].ID != EntityID)
		{
			return nullptr;
		}

		uint16_t ComponentID = GetComponentTypeID<T>();

		// Check if we already have a pool for this component
		// If not assign memory for it
		if (ComponentPools.size() <= ComponentID)
		{
			ComponentPools.resize(ComponentID + 1, nullptr);
		}

		//Then create a new memory pool
		if (ComponentPools[ComponentID] == nullptr)
		{
			ComponentPools[ComponentID] = new ComponentPool(sizeof(T));
		}


		T* AssignedComponent = new (ComponentPools[ComponentID]->Get(Index)) T();

		Entities[Index].Mask.set(ComponentID);
		return AssignedComponent;
	}


	template<typename T>
	void Remove(EntityID EntityID)
	{
		EntityIndex Index = Entity::GetEntityIndex(EntityID);
		if (Entities[Index].ID != EntityID)
		{
			return;
		}

		uint16_t ComponentID = GetComponentTypeID<T>();
		Entities[Index].Mask.reset(ComponentID);
	}

};

