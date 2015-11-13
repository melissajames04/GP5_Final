#pragma once
#include <SDL/SDL.h>
#include <string>
#include "Texture.h"
#include "AssetManager.h"
class GameObject
{
public:
	GameObject();
	~GameObject();
	SDL_Texture* loadTX;
	SDL_Surface* loadedImage;
	SDL_Rect pos;
	void loadImage(SDL_Renderer* renderer, const std::string& imageName);
	Texture* objTexture;
	AssetManager* asset;
	SDL_Point* GetOrigin(bool center);
	void Draw(int x, int y, float scale, SDL_Rect* Clip, double Angle, bool Center, SDL_RendererFlip Flip);
	void Animate(int x, int y, float scale, SDL_Rect* Clip, double Angle, bool Center, SDL_RendererFlip Flip,  int frameCount);

private:
	SDL_Point* origin;
	void SetRect();
	bool anim;
};

