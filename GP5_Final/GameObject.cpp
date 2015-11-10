#include "GameObject.h"
#include "Debug.h"

GameObject::GameObject() {
	pos.x = pos.y = pos.w = pos.h = 100;
}

GameObject::~GameObject() {
	SDL_FreeSurface(loadedImage);
	loadedImage = NULL;
}

void GameObject::loadImage(std::string imageName) {
	loadedImage = SDL_LoadBMP(imageName.c_str());
	if (loadedImage == NULL)
		Debug::Log(EMessageType::FATAL_ERROR, std::string(SDL_GetError()), __FILE__, __LINE__);
}

SDL_Texture* GameObject::render(SDL_Renderer* renderer, SDL_Surface* surface) {
	SDL_SetColorKey(loadedImage, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0, 0));
	loadTX = SDL_CreateTextureFromSurface(renderer, loadedImage);
	return (SDL_CreateTextureFromSurface(renderer, loadedImage));
}

