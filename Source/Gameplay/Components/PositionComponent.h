#pragma once
#include "../../Core/ECS.h"

class PositionComponent : public Component
{

public:

	// Component Overrides
	void Init() override
	{
	}

	void Update(double DeltaTime) override
	{
		YPos++;
		XPos++;
	}

	// PositionComponent Methods
	
	PositionComponent()
	{
		XPos = 0;
		YPos = 0;
	}

	PositionComponent(int32_t InXPos, int32_t InYPos)
	{
		XPos = InXPos;
		YPos = InYPos;
	}

	int32_t X() { return XPos; }
	int32_t Y() { return YPos; }

	void SetPos(int32_t X, int32_t Y)
	{
		XPos = X;
		YPos = Y;
	}

private:
	int32_t XPos = 0;
	int32_t YPos = 0;

};

