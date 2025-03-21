#pragma once
#include <cstdint>
#include "../../Core/ECS/ECS.h"


struct TransformComponent 
{
	TransformComponent() = default;
	TransformComponent(double InXPos, double InYPos)
	{
		XPos = InXPos;
		YPos = InYPos;
	}

	int32_t RectPosX{ 0 };
	int32_t RectPosY{ 0 };

	double XPos{ 0 };
	double YPos{ 0 };
};