#include "GameObject.h"
#include "Debug.h"
#include "Texture.h"
#include "SDL_image.h"

GameObject::GameObject(){
	pos.x = pos.y = 100;
	pos.w = pos.h = 204;
}

GameObject::~GameObject(){
	//SDL_FreeSurface(loadedImage);
	//loadedImage = NULL;
}

void GameObject::loadImage(SDL_Renderer* renderer, const std::string& imageName){
	//loadedImage = SDL_LoadBMP(imageName.c_str());
	objTexture = new Texture(renderer);
	objTexture->Load(imageName.c_str());
	objTexture->SetTexture(*objTexture->GetTexture(), pos.w, pos.h);
	objTexture->SetAlpha(1);
	objTexture->SetColor(255, 255, 255, 1);
	objTexture->SetBlendMode(SDL_BLENDMODE_NONE);
	loadedImage = IMG_Load(imageName.c_str());
}

SDL_Texture* GameObject::render(SDL_Renderer* renderer){
	//SDL_SetColorKey(loadedImage, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0, 0));
	//loadTX = SDL_CreateTextureFromSurface(renderer, loadedImage);
	printf("drawing");
	//{ x, y, scale, Clip, Angle, Center, Flip }
	//objTexture->Draw(pos.x, pos.y, 1.0f, &pos, 0.0, new SDL_Point{ pos.w/2, pos.x/2}, SDL_FLIP_NONE);
	return (SDL_CreateTextureFromSurface(renderer, loadedImage));
}

void GameObject::render2(SDL_Renderer* renderer, SDL_Surface* surface){
	objTexture->SetCurrentRenderer(renderer);
	objTexture->SetCurrentSurface(surface);
	objTexture->Draw(pos.x, pos.y, 1.0f, &pos,0.0, GetOrigin(true), SDL_FLIP_NONE);
}

SDL_Point* GameObject::GetOrigin(bool center){
	if (center)
		return (new SDL_Point{ pos.w / 2, pos.h / 2 });
	else
		return (new SDL_Point{ 0, 0 });
}

