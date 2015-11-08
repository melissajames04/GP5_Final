#include "Texture.h"
#include "Debug.h"
#include "SDL_image.h"

Texture::Texture(SDL_Renderer* sdlRenderer) : SDLTexture(nullptr), SDLRenderer(sdlRenderer), Width(0), Height(0){
}

Texture::~Texture(){
	Destroy();
}

bool Texture::Load(const std::string& FileName){
	Destroy();
	SDL_Texture* NewSDLTexture = nullptr;
	SDL_Surface* LoadedSurface = IMG_Load(FileName.c_str());

	if (!LoadedSurface){
		Debug::Log(EMessageType::ERROR, "Failed to load" + FileName + "! SDL Error: " + SDL_GetError(), __FILE__, __LINE__);
	}
	else{
		if (SDL_SetColorKey(LoadedSurface, SDL_TRUE, SDL_MapRGB(LoadedSurface->format, 0, 0xFF, 0xFF)) < 0){
			Debug::Log(EMessageType::WARNING, "Failed to set color key for " + FileName + ". SDL Error: " + SDL_GetError(), __FILE__, __LINE__);
		}
		NewSDLTexture = SDL_CreateTextureFromSurface(SDLRenderer, LoadedSurface);
		if (!NewSDLTexture){
			Debug::Log(EMessageType::ERROR, "Failed to create texture from " + FileName + "! SDL Error: " + SDL_GetError(), __FILE__, __LINE__);
		}
		else{
			Width = LoadedSurface->w;
			Height = LoadedSurface->h;
			Debug::Log(EMessageType::INFO, "Loaded texture " + FileName, __FILE__, __LINE__);
		}
		SDL_FreeSurface(LoadedSurface);
		LoadedSurface = nullptr;
	}
	SDLTexture = NewSDLTexture;
	return SDLTexture != nullptr;
}
