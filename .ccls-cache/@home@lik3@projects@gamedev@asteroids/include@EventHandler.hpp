#ifndef EVENT_HANDLER
#define EVENT_HANDLER

#include <SDL3/SDL.h>
#include "Player.hpp"

class EventHandler {
	public:
		static void handleKeyboard(Player& player);
	private:
		static SDL_Event e;
};

#endif
