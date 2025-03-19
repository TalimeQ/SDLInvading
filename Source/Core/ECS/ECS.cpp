#pragma once
#include "ECS.h"





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