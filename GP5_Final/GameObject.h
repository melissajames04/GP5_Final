#pragma once
#include <SDL/SDL.h>
#include <string>
#include "Texture.h"
class GameObject
{
public:
	GameObject();
	~GameObject();
	SDL_Texture* loadTX;
	SDL_Surface* loadedImage;
	SDL_Rect pos;
	void loadImage(SDL_Renderer* renderer, const std::string imageName);
	void render();
	Texture* objTexture;
};

