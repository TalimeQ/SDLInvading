#include "InputHandler.h"
#include "SDL.h"
#include <iostream>


void InputHandler::ParseKeyboard(SDL_Event* Event)
{
	// Having key down will treager repeating event, this will fix that
	if (Event->key.repeat != 0)
	{
		return;
	}

	switch (Event->type)
	{
	case SDL_KEYDOWN:
		OnKeyChanged(Event->key.keysym.sym, SDL_KEYDOWN);
		break;
	case SDL_KEYUP:
		OnKeyChanged(Event->key.keysym.sym, SDL_KEYUP);
		break;
	default:
		break;
	}
}

void InputHandler::OnKeyChanged(SDL_Keycode Key, SDL_EventType Event)
{
	auto Search = InputMap.find(Key);

	if (!(Search != InputMap.end()))
	{
		// Assume that the first time the key is pressed the button is down
		InputMap.emplace(std::make_pair(Key, true));

		// Broadcast event OnKeyDown
	}

	if (Event == SDL_KEYDOWN)
	{
		InputMap[Key] = true;
		// Broadcast event OnKeyDown
		std::cout << "Key Pressed" << std::endl;
	}
	else
	{
		InputMap[Key] = false;
		// Broadcast event OnKeyUP
		std::cout << "Key Released" << std::endl;
	}
}
