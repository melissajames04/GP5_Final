#pragma once
#include <SDL/SDL.h>
#include <string>


//The GameObject uses the SDL prebuilt in bmp loader to load in an image for temporary use inside of the project


class GameObject {
	public:
		GameObject();
		~GameObject();

		SDL_Surface* loadedImage;
		SDL_Texture* loadTX;
		SDL_Rect pos;
	
		void loadImage(std::string imageName);
	
		SDL_Texture* render(SDL_Renderer* renderer, SDL_Surface* surface);
};

