//#ifndef INPUTMANAGER_H
//#define INPUTMANAGER_H
//#include<string>
//using namespace std;
//
//class InputManager
//{
//public:
//	static void Initialize(
//		SDL_Keycode left,
//		SDL_Keycode right,
//		SDL_Keycode up,
//		SDL_Keycode down,
//		SDL_Keycode jump,
//		SDL_Keycode other);
//	static void Initialize(SDL_Keycode quit, SDL_Keycode pause);
//	InputManager() = delete;
//	InputManager(const InputManager&) = delete;
//	InputManager(InputManager&&) = delete;
//	InputManager& operator = (const InputManager&) = delete;
//	InputManager& operator = (InputManager&&) = delete;
//	static string Update();
//private:
//	static SDL_Keycode left, right, up, down, jump, other, quit, pause;
//	static string KeyEventHandler(SDL_Keycode key) ;
//};
//
//#endif