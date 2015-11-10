#include "AssetManager.h"
#include "SDL_image.h"
#include "Debug.h"

AssetManager::AssetManager():loadedAsset(nullptr), createdTexture(nullptr){}


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
		if (!createdTexture){
			Debug::Log(EMessageType::ERROR, "Failed to creat texture from " + fileName + ". SDL Error: " + SDL_GetError(), __FILE__, __LINE__);
		}
		SDL_FreeSurface(loadedAsset);
		loadedAsset = nullptr;
		return true;
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
	SDL_RenderCopyEx(renderer, createdTexture,NULL, Params.Clip, Params.Angle, Params.origin, Params.Flip);
}


