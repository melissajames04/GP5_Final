#include "InputManager.h"
#include <vector>
#include "SDL.h"
struct keyBind{
	int name;
	SDL_Keycode key;
};
static std::vector<keyBind> boundKeys;
int InputManager::mover = 0;
static keyBind lastKey;

void InputManager::initialize(int keyCount){
	boundKeys.reserve(keyCount);
}
void InputManager::bind(SDL_Keycode key, int func){
	keyBind _kb = keyBind{ func, key};
	boundKeys.push_back(_kb);
}
void InputManager::clearBinds(){
	boundKeys.clear();
}
int InputManager::Update(){
	SDL_Event SDLEvent;
	while (SDL_PollEvent(&SDLEvent)){
		if (SDLEvent.type == SDL_QUIT)
			exit(0);
		if (SDLEvent.type == SDL_KEYDOWN){
			if (lastKey.key == SDLEvent.key.keysym.sym)
				return lastKey.name;
			else
				return KeyEventHandler(SDLEvent.key.keysym.sym);
		}
		if (SDLEvent.type == SDL_KEYUP)
			return -1;
		if (SDLEvent.type == SDL_MOUSEBUTTONDOWN)
			return 0;
	}
}

int InputManager::KeyEventHandler(SDL_Keycode key){
	for (auto &b : boundKeys) {
		if (b.key == key){
			lastKey = b;
			return b.name;
		}
	}
}
