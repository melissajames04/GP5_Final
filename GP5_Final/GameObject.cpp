#include "GameObject.h"
#include "Debug.h"
#include "Texture.h"

GameObject::GameObject(){
	pos.x = pos.y = pos.w = pos.h = 100;
}

GameObject::~GameObject(){
	//SDL_FreeSurface(loadedImage);
	//loadedImage = NULL;
}

void GameObject::loadImage(SDL_Renderer* renderer, const std::string imageName){
	//loadedImage = SDL_LoadBMP(imageName.c_str());
	objTexture = new Texture(renderer);
	objTexture->Load(imageName.c_str());
	objTexture->SetTexture(*objTexture->GetTexture(), pos.w, pos.h);
	
}

void GameObject::render(){
	//SDL_SetColorKey(loadedImage, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0, 0));
	//loadTX = SDL_CreateTextureFromSurface(renderer, loadedImage);
	printf("drawing");
	objTexture->Draw(pos.x, pos.y, 1.0f, &pos, 0.0, nullptr, SDL_FLIP_NONE);
	//return (SDL_CreateTextureFromSurface(renderer, objTexture->GetTexture()));
}

