#ifndef WINDOW_H
#define WINDOW_H
#include "SDL.h"
class Window
{
public:
	Window();
	Window(const Window&) = delete;
	Window(Window&&) = delete;
	Window& operator = (const Window&) = delete;
	Window& operator= (Window&&) = delete;
	~Window();
	bool Initialize();
	void Shutdown();
	void ClearRenderer() const;
	void SetWindowSize(const int width_, const int height_);
	void ToggleFullScreen();
	SDL_Renderer* GetRenderer() const;
	int GetWidth() const;
	int GetHeight() const;
	SDL_Surface* getSurface();
	void render();
	int convertX(float _numX, float _maxX);
	int convertY(float _numY, float _maxY);
	SDL_Rect winRect;

private:
	SDL_Window* SDLWindow;
	SDL_Renderer* SDLRenderer;
	SDL_Surface* SDLSurface;
	int Width;
	int Height;
	bool isFullScreen;
	bool isInitialized;
};
#endif

