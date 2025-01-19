#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

// This is based on tutorial more then my own writing

class Component;
class Entity;

using ComponentID = size_t;

// Each component has its unique ID
// Physics for example 1
// Input 2 .. etc
inline ComponentID  GetComponentID()
{
	static ComponentID LastID = 0;
	return LastID++;
}

// The ComponentID will be generated here again for each unique <type T>
// Basically ensures each component has unique id!
template <typename T> inline ComponentID GetComponentTypeID() noexcept
{
	static ComponentID TypeID = GetComponentID();
	return TypeID;
}

// Max components for entity
constexpr size_t MaxComponents = 32;

// 32 bits, One signalizes that we have the component 
// 0 that we have not
using ComponentBitSet = std::bitset<MaxComponents>;

//Storing components
using ComponentArray = std::array<Component*, MaxComponents>;

class Component
{
public:
	Entity* entity;

	virtual void Init() {};
	virtual void Update(double DeltaTime) {};
	virtual void Draw() {};

	virtual ~Component() {};
};

class Entity
{
public:
	void Update(double DeltaTime)
	{
		for (auto& Component : ComponentList)
		{
			Component->Update(DeltaTime);
		}
	}

	// TODO refactor for sure!
	void Draw()
	{
		for (auto& Component : ComponentList)
		{
			Component->Draw();
		}
	}

	void Destroy(){bIsActive = false;}
	bool IsActive() { return bIsActive; };


private:
	bool bIsActive{ true };
	
	// I guess unique here so that we remove component 
	// when its entity dies
	std::vector<std::unique_ptr<Component>> ComponentList;

	ComponentArray ComponentArray;
	ComponentBitSet ComponentBitSet;

public:
	template <typename Type> bool HasComponent() const
	{
		return ComponentBitSet[GetComponentTypeID<Type>()];
	}

	template <typename T, typename... TArgs>
	T& AddComponent(TArgs&&... ConstrArgs)
	{
		T* CreatedComponent(new T(std::forward<TArgs>(ConstrArgs)...));
		CreatedComponent->entity = this;

		// Does he need a unique ptr here?
		std::unique_ptr<Component> UniquePtr{CreatedComponent};
		ComponentList.emplace_back(std::move(UniquePtr));

		// This has little sense to me
		ComponentArray[GetComponentTypeID<T>()] = CreatedComponent;
		ComponentBitSet[GetComponentTypeID<T>()] = true;

		CreatedComponent->Init();
		return *CreatedComponent;
	}

	// Dunno if the guy from a tut is a genius or a madman
	template<typename T> T& GetComponent() const
	{
		auto ptr(ComponentArray[GetComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
};

class EntityManager
{
public:
	void Update(double DeltaTime)
	{
		for (auto& Entity : Entities)
		{
			Entity->Update(DeltaTime);
		}
	}
	void Draw()
	{
		for (auto& Entity : Entities)
		{
			Entity->Draw();
		}
	}

	void Refresh()
	{
		Entities.erase(std::remove_if(std::begin(Entities), std::end(Entities),
			[](const std::unique_ptr<Entity>& CheckedEntity)
			{
				return !CheckedEntity->IsActive();
			}),
			std::end(Entities));
	}

	Entity& AddEntity()
	{
		Entity* NewEntity = new Entity();
		std::unique_ptr<Entity> EntityPtr{ NewEntity };
		Entities.emplace_back(std::move(EntityPtr));

		return *NewEntity;
	}

private:
	std::vector<std::unique_ptr<Entity>> Entities;

};