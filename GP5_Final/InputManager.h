#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include<string>
#include <vector>
#include "SDL.h"
using namespace std;

class InputManager{

public:
	static int Update();
	static void bind(SDL_Keycode key, int func);
	static void clearBinds();
	static int KeyEventHandler(SDL_Keycode key);
	static void initialize(int keyCount);
	static int mover;

	InputManager() = delete;
	InputManager(const InputManager&) = delete;
	InputManager(InputManager&&) = delete;
	InputManager& operator = (const InputManager&) = delete;
	InputManager& operator = (InputManager&&) = delete;
	//static SDL_Keycode lastKey;
	//static 
	
	
};

#endif