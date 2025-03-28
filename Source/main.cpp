#include "SDL.h"
#include "Core/Game.h"



int main(int agrc, char* argv[])
{
	Game GameInstance{};

	GameInstance.Initialize("Invading Forces 4", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);


	uint32_t CurrentTicks{0}, LastTicks{ 0 };
	double Accumulator{0.0f};

	const uint32_t TicksInSecond{1000};
	const uint32_t TargetFPS{60};

	constexpr double TargetDeltaTicks{ (double)TicksInSecond / (double)TargetFPS};
	constexpr double TargetDelta{ (double)TargetDeltaTicks / (double)TicksInSecond };

	while (GameInstance.IsRunning())
	{
		uint32_t CurrentTicks = SDL_GetTicks();
		uint32_t DeltaTicks = CurrentTicks - LastTicks;

		LastTicks = SDL_GetTicks();
		Accumulator += (double)DeltaTicks;

		while (Accumulator > TargetDeltaTicks)
		{
			GameInstance.HandleEvents();
			GameInstance.Update(TargetDelta);
			Accumulator -= TargetDeltaTicks;
		}
	
		GameInstance.Render();
	}

	return 0;
}