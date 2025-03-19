#pragma once
#include "../../Core/ECS/ECS.h"

// TODO verify if should not be refactored

class PlayerControllerSystem
{

public:
	void UpdateShipTransform(double DeltaTime, Scene& SceneRef);


private:
	double Speed = 300.0f;

};

