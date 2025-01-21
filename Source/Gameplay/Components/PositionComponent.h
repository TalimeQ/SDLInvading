#pragma once
#include "../../Core/SimpleECS.h"


struct PositionComponentMovable 
{
	PositionComponentMovable() = default;
	PositionComponentMovable(double InXPos, double InYPos)
	{
		XPos = InXPos;
		YPos = InYPos;
	}

	int32_t RectPosX{ 0 };
	int32_t RectPosY{ 0 };

	double XPos{ 0 };
	double YPos{ 0 };

	double RequestedXTranslation{ 0 };
	double RequestedYTranslation{ 0 };
};