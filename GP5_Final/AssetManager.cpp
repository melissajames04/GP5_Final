#include "AssetManager.h"
#include "SDL_image.h"
#include "Debug.h"

AssetManager::AssetManager() :loadedAsset(nullptr), createdTexture(nullptr), Width(0), Height(0), frameCount(0), previousFrame(0){}

AssetManager::~AssetManager(){
	Destroy();
}

void AssetManager::Destroy(){
	SDL_DestroyTexture(createdTexture);
	createdTexture = nullptr;
	renderer = nullptr;
}

bool AssetManager::LoadAsset(SDL_Renderer* _renderer, const std::string& fileName){
	Destroy();
	renderer = _renderer;
	loadedAsset = IMG_Load(fileName.c_str());
	if (!loadedAsset){
		Debug::Log(EMessageType::ERROR, "Failed to load" + fileName + "! SDL Image Error:" + IMG_GetError(), __FILE__, __LINE__);
		return false;
	}
	else{
		createdTexture = SDL_CreateTextureFromSurface(renderer, loadedAsset);
		Width = loadedAsset->w;
		Height = loadedAsset->h;
		if (!createdTexture){
			Debug::Log(EMessageType::ERROR, "Failed to creat texture from " + fileName + ". SDL Error: " + SDL_GetError(), __FILE__, __LINE__);
		}
		else{
			SDL_FreeSurface(loadedAsset);
			loadedAsset = nullptr;
			return true;
		}
	}
}

void AssetManager::Draw(int x, int y, float scale, SDL_Rect* Clip, double Angle, bool Center, SDL_RendererFlip Flip){
	DrawParams Params = DrawParams{ x, y, scale, Clip, Angle, SetOrigin(Center, Clip), Flip };
	Draw(Params);
}

SDL_Point* AssetManager::SetOrigin(bool center, SDL_Rect* Clip){
	if (center)
		return (new SDL_Point{ Clip->w / 2, Clip->h / 2 });
	else
		return (new SDL_Point{ 0, 0 });
}

void AssetManager::Draw(const DrawParams& Params) const{
	SDL_Rect DrawRect = {
		(int)(Params.x + (-Width * (Params.scale - 1.0f) * 0.5f)),
		(int)(Params.y + (-Height * (Params.scale - 1.0f) * 0.5f)),
		(int)(Width * Params.scale),
		(int)(Height * Params.scale) };
	if (Params.Clip){
		DrawRect.w = Params.Clip->w;
		DrawRect.h = Params.Clip->h;
	}
	SDL_RenderCopyEx(renderer, createdTexture, NULL, &DrawRect, Params.Angle, Params.origin, Params.Flip);
}

void AssetManager::SetBlendMode(const SDL_BlendMode blend){
	SDL_SetTextureBlendMode(createdTexture, SDL_BLENDMODE_BLEND);
}
int AssetManager::GetHeight(){
	return Height;
}
int AssetManager::GetWidth(){
	return Width;
}

void AssetManager::Animate(int x, int y, float scale, SDL_Rect* Clip, double Angle, bool Center, SDL_RendererFlip Flip,  int frameCount, int margin){
	DrawParams Params = DrawParams{ x, y, scale, Clip, Angle, SetOrigin(Center, Clip), Flip };
	Animate(Params, frameCount, margin);
}

void AssetManager::Animate(const DrawParams& Params,  int frameCount, int margin){
	SDL_Rect ClipRect = {
		(Params.x + (-Width * (Params.scale - 1.0f) * 0.5f)),
		(Params.y + (-Height * (Params.scale - 1.0f) * 0.5f)),
		Width/frameCount * Params.scale,
		(Height * Params.scale) };
	if (Params.Clip){
		DrawRect.w = Params.Clip->w;
		DrawRect.h = Params.Clip->h;
	}

	if (previousFrame + 1 > frameCount ){
		previousFrame = 0;
	}
	SDL_Rect DrawRect = {  ((previousFrame) * (Width/frameCount) * Params.scale), 
							0,
							(Width / frameCount) * Params.scale,
							Height * Params.scale };
		previousFrame = previousFrame + 1;
		SDL_RenderCopyEx(renderer, createdTexture, &DrawRect, &ClipRect, Params.Angle, Params.origin, Params.Flip);
}



