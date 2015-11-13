//#include "InputManager.h"
//#include "SDL.h"
//
//void InputManager::Initialize(
//						SDL_Keycode _left, 
//						SDL_Keycode _right,
//						SDL_Keycode _up,
//						SDL_Keycode _down,
//						SDL_Keycode _jump,
//						SDL_Keycode _other){
//	left = _left;
//	right = _right;
//	up = _up;
//	down = _down;
//	jump = _jump;
//	other = _other;
//}
//
//void InputManager::Initialize(SDL_Keycode _quit,SDL_Keycode _pause){
//	quit = _quit;
//	pause = _pause;
//}
//string InputManager::Update(){
//	SDL_Event SDLEvent;
//	while (SDL_PollEvent(&SDLEvent)){
//		switch (SDLEvent.type){
//		case SDL_QUIT:
//			exit(0);
//			return 0;
//			break;
//		case SDL_KEYDOWN:
//			return KeyEventHandler(SDLEvent.key.keysym.sym);
//			break;
//		case SDL_MOUSEBUTTONDOWN:
//			return 0;
//			break;
//		default:
//			break;
//		}
//	}
//}
//
//string InputManager::KeyEventHandler(SDL_Keycode key){
//	if (key == right)
//		return "right";
//	else if (key == left)
//		return "left";
//	else if (key == up)
//		return "up";
//	else if (key == down)
//		return "down";
//	else if (key == jump)
//		return "jump";
//	else if (key == other)
//		return "other";
//	else
//		return "unknown";
//
//
//}
