#include "ECS.h"


template<typename T>
T Scene::Assign(EntityID EntityID)
{
	// Checkup if entity is valid
	EntityIndex Index = Entity::GetEntityIndex(EntityID);
	if (Entities[Index].ID != EntityID)
	{
		return;
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

	
	EntityIndex Index = Entity::GetEntityIndex(EntityID);
	T AssignedComponent = new (ComponentPools[ComponentID]->Get(Index)) T();

	Entities[Index].Mask.set(ComponentID);
	return AssignedComponent;
}

template<typename T>
T Scene::GetComponentFromEntity(EntityID EntityID)
{
	EntityIndex Index = Entity::GetEntityIndex(EntityID);
	if (Entities[Index].ID != EntityID)
	{
		return;
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
void Scene::Remove(EntityID EntityID)
{
	EntityIndex Index = Entity::GetEntityIndex(EntityID);
	if (Entities[Index].ID != EntityID)
	{
		return;
	}

	uint16_t ComponentID = GetComponentTypeID<T>();
	Entities[Index].Mask.reset(ComponentID);
}

void Scene::DestroyEntity(EntityID InEntityID)
{
	EntityID NewID = Entity::CreateEntityID(EntityIndex(-1), Entity::GetEntityVersion(InEntityID) + 1);
	Entities[Entity::GetEntityIndex(InEntityID)].ID = NewID;
	Entities[Entity::GetEntityIndex(InEntityID)].Mask.reset();
	FreeEntities.push_back(Entity::GetEntityIndex(InEntityID));
}

EntityID Scene::NewEntity()
{
	if (!FreeEntities.empty())
	{
		EntityIndex NewIndex = FreeEntities.back();
		FreeEntities.pop_back();

		EntityID NewID = Entity::CreateEntityID(NewIndex, Entity::GetEntityVersion(Entities[NewIndex].ID));
		Entities[NewIndex].ID = NewID;
		return Entities[NewIndex].ID;
	}


	// Create a new version of entity (with 0!)
	Entities.push_back({ Entity::CreateEntityID(EntityIndex(Entities.size()),0), ComponentMask() });
	return Entities.back().ID;
}