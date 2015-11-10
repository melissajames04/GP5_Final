#include "Window.h"
#include <sstream>
#include "Debug.h"



//The main Window file that controls the viewable window in it's size and rendering
//
//Used by the Game Scene Manager to make an ineractive window and modify it's sizing and rendering when accessed
//
//Initialization is a bool that defaults to negative until ran and returns true, this is so that at start up it creates a window, but later
//won't create more windows(since the game only needs one). Inside initialization it goes around and checks if everything needed for a window
//has been created, and creates it if not, and then checks to see if it was created or not after
//
//The rendering section is all for getting the screen at it's current moment, clearing it, then re-rendering it to refresh the screen
//
//The window sizing section is for setting the size of the screen, toggling it's fullscreen on or off, getting it's dimensions, and
//converting x and y coordinates into a real world space within the game



//----------INITIALIZATION----------//
	Window::Window() :SDLWindow(nullptr), SDLRenderer(nullptr), SDLSurface(nullptr), Width(0), Height(0), isInitialized(false), isFullScreen(false) {

	}

	Window::~Window() {
		Shutdown();
	}

	bool Window::Initialize() {
		isInitialized = false;

		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
			Debug::Log(EMessageType::FATAL_ERROR, std::string(SDL_GetError()), __FILE__, __LINE__);
			return isInitialized = false;
		}

		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			Debug::Log(EMessageType::WARNING, "Linear texture filtering is not enabled.", __FILE__, __LINE__);
		}

		SDLWindow = SDL_CreateWindow("SDL Example Project", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winRect.w, winRect.h, SDL_WINDOW_SHOWN);
	
		if (!SDLWindow) {
			Debug::Log(EMessageType::FATAL_ERROR, "Failed to create a window!", __FILE__, __LINE__);
			Shutdown();
			return false;
		}

		SDLRenderer = SDL_CreateRenderer(SDLWindow, -1, SDL_RENDERER_ACCELERATED);
	
		if (!SDLRenderer) {
			Debug::Log(EMessageType::FATAL_ERROR, std::string(SDL_GetError()), __FILE__, __LINE__);
			Shutdown();
			return false;
		}

		SDL_SetRenderDrawColor(SDLRenderer, 127, 127, 127, 255);
		SDL_RenderPresent(SDLRenderer);
		SDLSurface = SDL_GetWindowSurface(SDLWindow);
	
		isInitialized = true;
		return true;
	}

	void Window::Shutdown() {
		SDL_FreeSurface(SDLSurface);
		SDLSurface = nullptr;
	
		SDL_DestroyRenderer(SDLRenderer);
		SDLRenderer = nullptr;
	
		SDL_DestroyWindow(SDLWindow);
		SDLWindow = nullptr;

		isInitialized = false;
	}




//----------RENDERING----------//
	void Window::ClearRenderer() const {
		SDL_SetRenderDrawColor(SDLRenderer, 0, 0, 0, 255);
		SDL_RenderClear(SDLRenderer);
	}

	SDL_Renderer* Window::GetRenderer() const {
		return SDLRenderer;
	}

	void Window::render() {
		SDL_RenderClear(SDLRenderer);
		SDL_RenderPresent(SDLRenderer);
	}




//----------WINDOW SIZING----------//
	void Window::SetWindowSize(const int width_, const int height_) {
		winRect.w = width_;
		winRect.h = height_;
	}

	void Window::ToggleFullScreen() {
		isFullScreen = !isFullScreen;
		SDL_SetWindowFullscreen(SDLWindow, (isFullScreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN));
	}

	int Window::GetWidth() const {
		return winRect.w;
	}

	int Window::GetHeight() const {
		return winRect.h;
	}

	SDL_Surface* Window::getSurface() {
		return SDLSurface;
	}

	int Window::convertX(float _numX, float _maxX) {
		float normX = _numX / _maxX;
		float finalX = (normX * (GetWidth() - 1) + 1);
		return int(finalX);
	}

	int Window::convertY(float _numY, float _maxY) {
		float normY = _numY / _maxY;
		float finalY = GetHeight() - (normY * (GetHeight() - 1) + 1);
		return int(finalY);
	}