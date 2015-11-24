#include "GameObject.h"
#include "Debug.h"
#include "Texture.h"
#include "SDL_image.h"

GameObject::GameObject(): anim(false){
	//pos.x = pos.y = 100;
	//pos.w = pos.h = 204;
}

GameObject::~GameObject(){
	//SDL_FreeSurface(loadedImage);
	//loadedImage = NULL;
}

void GameObject::loadImage(SDL_Renderer* renderer,const std::string& imageName){
	asset = new AssetManager();
	asset->LoadAsset(renderer, imageName.c_str());
	asset->SetBlendMode(SDL_BLENDMODE_BLEND);
	//SetRect();
}

int GameObject::getHeight(){
	return asset->GetHeight();
}

int GameObject::getWidth(){
	return asset->GetWidth();
}

void GameObject::SetRect(){
	pos.x = pos.y = 100;
	pos.w = asset->GetWidth();
	pos.h = asset->GetHeight();
}
void GameObject::Draw(int x, int y, float scale, SDL_Rect* Clip, double Angle, bool Center, SDL_RendererFlip Flip){	
	pos = { x, y, asset->GetWidth(), asset->GetHeight() };
	asset->Draw(pos.x, pos.y, scale, &pos, Angle, Center, Flip);
}

void GameObject::Animate(int x, int y, float scale, SDL_Rect* Clip, double Angle, bool Center, SDL_RendererFlip Flip, int frameCount){
	anim = true;
	pos = { x, y, asset->GetWidth(), asset->GetHeight() };
	asset->Animate(pos.x, pos.y, scale, &pos, Angle, Center, Flip, frameCount );
}
SDL_Point* GameObject::GetOrigin(bool center){
	if (center)
		return (new SDL_Point{ pos.w / 2, pos.h / 2 });
	else
		return (new SDL_Point{ 0, 0 });
}

