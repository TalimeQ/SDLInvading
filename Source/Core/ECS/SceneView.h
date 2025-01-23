#pragma once
#include "ECS.h"
#include "SDL.h"

template<typename ... ComponentTypes>
struct SceneView
{
	SceneView() {}
	SceneView(Scene& InScene) : ScenePointer(&InScene)
	{
		if (sizeof ... (ComponentTypes) == 0)
		{
			All = true;
		}
		else
		{
			uint16_t ComponentIDs = { 0 ,GetComponentTypeID<ComponenTypes>() ...};
			for (uint16_t i = 1; i < (sizeof.. (ComponentTypes)+ 1 ); i++)
			{
				Mask.Set(ComponentIDs[i])
			}
		}
	}

	Scene* ScenePointer{ nullptr };
	ComponentMask Mask;
	bool bAll{ false };

	struct Iterator
	{
		Iterator() {}
		Iterator(Scene* InScene, EntityIndex InIndex, ComponentMask InMask, bool bInAll)
			: ScenePointer(InScene), Index(InIndex), Mask(InMask), bAll(bInAll) {
		}


		EntityIndex Index;
		Scene* ScenePointer;
		ComponentMask Mask;
		bool bAll{ false };

		bool ValidIndex()
		{
			return Entity::IsEntityValid(ScenePointer->Entities[Index].ID) &&
				(bAll || Mask == (Mask & ScenePointer->Entities[Index].Mask));
		}

		EntityID operator*() const
		{
			return ScenePointer->Entities[Index].ID;
		}

		bool operator==(const Iterator& other) const
		{
			return Index == other.Index || Index == ScenePointer->Entities.size();
		}

		bool operator!=(const Iterator& other) const
		{
			return Index != other.Index || Index != ScenePointer->Entities.size();
		}

		Iterator& operator++()
		{
			do
			{
				Index++;
			} while (Index < ScenePointer->Entities.size() && !ValidIndex());
			return *this;
		}
	};

	const Iterator begin() const
	{
		uint16_t FirstIndex = 0;
		while(FirstIndex < ScenePointer->Entities.size() && (Mask != (Mask & ScenePointer->Entities[FirstIndex].Mask) ||
			!Entity::IsEntityValid(ScenePointer->Entities[FirstIndex].ID))
		{
			FirstIndex++;
		}

		return Iterator(ScenePointer, FirstIndex, Mask, bAll);
	}

	const Iterator end() const
	{
		return Iterator(ScenePointer, EntityIndex(ScenePointer->Entities.size()),Mask, bAll);
	}
};

