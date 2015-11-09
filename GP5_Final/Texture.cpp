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
	//SDL_Surface* LoadedSurface = nullptr;
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

void Texture::SetTexture(SDL_Texture& SDLTexture_, const int Width_, const int Height_){
	Destroy();
	SDLTexture = &SDLTexture_;
	Width = Width_;
	Height = Height_;
}

void Texture::Destroy(){
	SDL_DestroyTexture(SDLTexture);
	SDLTexture = nullptr;
	Width = 0;
	Height = 0;
}

void Texture::Draw(const DrawParams& Params) const{
	SDL_Rect DrawRect = {
		(int)(Params.x + (-Width * (Params.scale - 1.0f) * 0.5f)),
		(int)(Params.y + (-Height * (Params.scale - 1.0f) * 0.5f)),
		(int)(Width * Params.scale),
		(int)(Height * Params.scale) };
	if (Params.Clip){
		DrawRect.w = Params.Clip->w;
		DrawRect.h = Params.Clip->h;
	}
	SDL_RenderCopyEx(SDLRenderer, SDLTexture, Params.Clip, &DrawRect, Params.Angle, Params.Center, Params.Flip);
}

void Texture::Draw(
	const int x,
	const int y,
	const float scale,
	SDL_Rect* Clip,
	const double Angle,
	SDL_Point* Center,
	const SDL_RendererFlip Flip) const{
	DrawParams Params = DrawParams{ x, y, scale, Clip, Angle, Center, Flip };
	Draw(Params);
}

void Texture::SetAlpha(const Uint8 A){
	SDL_SetTextureAlphaMod(SDLTexture, A);
}

void Texture::SetBlendMode(const SDL_BlendMode BlendMode){
	SDL_SetTextureBlendMode(SDLTexture, BlendMode);
}

void Texture::SetColor(const SDL_Color& SDLColor){
	SetColor(SDLColor.r, SDLColor.g, SDLColor.b, SDLColor.a);
}

void Texture::SetColor(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a){
	SDL_SetTextureColorMod(SDLTexture, r, g, b);
	SDL_SetTextureAlphaMod(SDLTexture, a);
}

int Texture::GetWidth() const{
	return Width;
}

int Texture::GetHeight() const{
	return Height;
}

SDL_Texture* Texture::GetTexture() const{
	return SDLTexture;
}
