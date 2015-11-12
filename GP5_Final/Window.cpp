#include "Window.h"
#include <sstream>
#include "Debug.h"

Window::Window() :SDLWindow(nullptr), SDLRenderer(nullptr), SDLSurface(nullptr), Width(0), Height(0), isInitialized(false), isFullScreen(false){}

Window::~Window(){
	Shutdown();
}

bool Window::Initialize(){
	isInitialized = false;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		Debug::Log(EMessageType::FATAL_ERROR, std::string(SDL_GetError()), __FILE__, __LINE__);
		return isInitialized = false;
	}
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")){
		Debug::Log(EMessageType::WARNING, "Linear texture filtering is not enabled.", __FILE__, __LINE__);
	}
	SDLWindow = SDL_CreateWindow("SDL Example Project", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winRect.w, winRect.h, SDL_WINDOW_SHOWN);
	if (!SDLWindow){
		Debug::Log(EMessageType::FATAL_ERROR, "Failed to create a window!", __FILE__, __LINE__);
		Shutdown();
		return false;
	}
	SDLRenderer = SDL_CreateRenderer(SDLWindow, -1, SDL_RENDERER_ACCELERATED);
	if (!SDLRenderer){
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

void Window::Shutdown(){
	printf("window shutdown");
		//SDL_FreeSurface(SDLSurface);
		SDLSurface = nullptr;
		SDL_DestroyRenderer(SDLRenderer);
		SDLRenderer = nullptr;
		SDL_DestroyWindow(SDLWindow);
		SDLWindow = nullptr;
		isInitialized = false;
}

void Window::SetWindowSize(const int width_, const int height_){
	winRect.w = width_;
	winRect.h = height_;
}

void Window::ClearRenderer() const{
	SDL_SetRenderDrawColor(SDLRenderer, 0, 0, 0, 255);
	SDL_RenderClear(SDLRenderer);
}

void Window::ToggleFullScreen(){
	isFullScreen = !isFullScreen;
	SDL_SetWindowFullscreen(SDLWindow, (isFullScreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN));
}

SDL_Renderer* Window::GetRenderer() const{
	return SDLRenderer;
}

void Window::render(){
	//SDL_UpdateWindowSurface(SDLWindow);
	//SDL_FillRect(SDLSurface, NULL, 0x7F7F7F);
	SDL_RenderClear(SDLRenderer);
	SDL_RenderPresent(SDLRenderer);
}

int Window::GetWidth() const{
	//return Width;
	return winRect.w;
}

int Window::GetHeight() const{
	//return Height;
	return winRect.h;
}

SDL_Surface* Window::getSurface(){
	return SDLSurface;
}

int Window::convertX(float _numX, float _maxX){
	float normX = _numX / _maxX;
	float finalX = (normX * (GetWidth() - 1) + 1);
	return int(finalX);
}

int Window::convertY(float _numY, float _maxY){
	float normY = _numY / _maxY;
	float finalY = GetHeight() - (normY * (GetHeight() - 1) + 1);
	return int(finalY);
}