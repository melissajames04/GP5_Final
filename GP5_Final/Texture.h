#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>
#include "SDL.h"
class Texture
{
	struct DrawParams{
		int x;
		int y;
		float scale;
		SDL_Rect* Clip;
		double Angle;
		SDL_Point* Center;
		SDL_RendererFlip Flip;
	};
public:
	explicit Texture(SDL_Renderer* Renderer);
	Texture(const Texture&) = delete;
	Texture(Texture&&) = delete;
	Texture& operator=(const Texture&) = delete;
	Texture& operator=(Texture&&) = delete;
	~Texture();
	bool Load(const std::string& FileName);
	void SetTexture(SDL_Texture& SDLTexture_, const int Width_, const int Height_);
	void Destroy();
	void Draw(const DrawParams& Params) const;
	void Draw(
		const int X = 0,
		const int Y = 0,
		const float Scale = 1,
		SDL_Rect* Clip = nullptr,
		const double Angle = 0,
		SDL_Point* Center = nullptr,
		const SDL_RendererFlip Flip = SDL_RendererFlip::SDL_FLIP_NONE) const;
	void SetAlpha(const Uint8 A);
	void SetBlendMode(const SDL_BlendMode BlendMode);
	void SetColor(const SDL_Color& Colour);
	void SetColor(const Uint8 R, const Uint8 G, const Uint8, const Uint8 A);
	int GetWidth() const;
	int GetHeight() const;
	SDL_Texture* GetTexture() const;
	void SetCurrentRenderer(SDL_Renderer* _SDLRenderer);
	void SetCurrentSurface(SDL_Surface* _SDLSurface);

private:
	//a handle to the asset
	SDL_Texture* SDLTexture;
	SDL_Renderer* SDLRenderer;
	SDL_Surface* LoadedSurface;
	SDL_Surface* SDLSurface;
	int Width, Height;

};

#endif