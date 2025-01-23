#pragma once
#include "ECS.h"

template<typename ... ComponentTypes>
struct SceneView
{

	SceneView()
	{

	}

	struct Iterator
	{
		Iterator() {}

		EntityID operator*() const
		{

		}

		bool operator==(const Iterator& other) const
		{
			// Compare two iterators
		}

		bool operator!=(const Iterator& other) const
		{
			// Similar to above
		}

		Iterator& operator++()
		{
			// Move the iterator forward
		}
	};

	const Iterator begin() const
	{
		// Give an iterator to the beginning of this view
	}

	const Iterator end() const
	{
		// Give an iterator to the end of this view 
	}
};

