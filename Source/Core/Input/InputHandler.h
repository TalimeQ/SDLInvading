#pragma once
#include <unordered_map>
#include "SDL.h"




class InputHandler
{
	// Input Handler Data
public:
	void ParseKeyboard(SDL_Event* Event);

	void OnKeyChanged(SDL_Keycode Key, SDL_EventType Event);

private:
	std::unordered_map<SDL_Keycode, bool> InputMap;
};

