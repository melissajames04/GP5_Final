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
	void loadImage(SDL_Renderer* renderer, const std::string& imageName);
	SDL_Texture* render(SDL_Renderer* renderer);
	Texture* objTexture;
	SDL_Point* GameObject::GetOrigin(bool center);
	void render2(SDL_Renderer* renderer, SDL_Surface* surface);
private:
	SDL_Point* origin;
};

