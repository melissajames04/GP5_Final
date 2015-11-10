#ifndef WINDOW_H
#define WINDOW_H
#include "SDL.h"


//The Window files are used to make an interactive screen for the user to use, allowing us to draw the various images that make up the game
//
//The two Window files are used by the GameSceneManager to create and manage a window used to display the game
//
//The starting SDL_ objects are used to create a window and surface to draw onto with the renderer, this will all be used and accessed by
//the GameSceneManager
//
//The rest of private simply holds variables to store the sizing of the window and a couple of bools for whether it's fullscreen and 
//initialized
//
//Starting in public is the standard constructor and destructor, as well as the deletes to get rid of the base constructors
//
//Next are the pair that control startup and shutdown of the window, with Initialize being a bool to say if it's initialized or not, being 
//checked directly to see if it's done it's job yet or not. Shutdown stays a void because we simply want to call it when the window is out
//of scope or being destroyed.
//
//The renderer and surface methods are all used to create a surface for the program to draw on and use for rendering, together they control
//the flow of visual information being output to the screen. Together they refresh the window by clearing it, getting the information to 
//render to, getting the information of what they're rendering to, and then rendering it before starting over
//
//The set window size and toggle fullscreen are fairly self explainatory, controlling the size of the screen
//
//Lastly are some public variables used to get the sizing of the surface, as well as set them to be more real world, as well as create a
//rectangle the size of the window to be used for SDL_Surface and drawing to it



class Window {
	private:
		SDL_Window* SDLWindow;
		SDL_Renderer* SDLRenderer;
		SDL_Surface* SDLSurface;

		int Width;
		int Height;

		bool isFullScreen;
		bool isInitialized;


	public:
		Window();
		~Window();

		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator = (const Window&) = delete;
		Window& operator= (Window&&) = delete;
		
		bool Initialize();
		void Shutdown();

		void ClearRenderer() const;		
		SDL_Renderer* GetRenderer() const;
		SDL_Surface* getSurface();
		void render();

		void SetWindowSize(const int width_, const int height_);
		void ToggleFullScreen();

		int GetWidth() const;
		int GetHeight() const;
		int convertX(float _numX, float _maxX);
		int convertY(float _numY, float _maxY);
		SDL_Rect winRect;
};
#endif

