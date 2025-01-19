#pragma once
#include "../../Core/ECS.h"

class PositionComponent : public Component
{
public:

	int32_t X() { return XPos; }
	int32_t Y() { return YPos; }

	void Init() override
	{
		XPos = 0;
		YPos = 0;
	}

	void Update(double DeltaTime) override
	{
		YPos++;
		XPos++;
	}

	void SetPos(int32_t X, int32_t Y)
	{
		XPos = X;
		YPos = Y;
	}

private:
	int32_t XPos = 0;
	int32_t YPos = 0;

};

