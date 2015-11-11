#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H
#include <string>
#include "SDL.h"

class AssetManager
{
	struct DrawParams{
		int x;
		int y;
		float scale;
		SDL_Rect* Clip;
		double Angle;
		SDL_Point* origin;
		SDL_RendererFlip Flip;
		SDL_Renderer* renderer;
		SDL_Surface* surface;
	};
public:
	AssetManager();
	AssetManager(const AssetManager&) = delete;
	AssetManager(AssetManager&&) = delete;
	AssetManager& operator = (const AssetManager&) = delete;
	AssetManager& operator=(AssetManager&&) = delete;
	~AssetManager();
	void Destroy();
	bool LoadAsset(SDL_Renderer* _renderer,const std::string& fileName);
	void Draw(
		int x,
		int y,
		float scale,
		SDL_Rect* Clip,
		double Angle,
		bool Center,
		SDL_RendererFlip Flip);
		void Draw(const DrawParams& Params) const;
		void SetBlendMode(const SDL_BlendMode blend);
		int GetHeight();
		int GetWidth();
		void Animate(int x, int y, float scale, SDL_Rect* Clip, double Angle, bool Center, SDL_RendererFlip Flip,  int frameCount, int margin);
		void Animate(const DrawParams& Params,  int frameCount, int margin);

private:
	SDL_Surface* loadedAsset;
	SDL_Rect DrawRect;
	SDL_Point* SetOrigin(bool center, SDL_Rect* Clip);
	SDL_Texture* createdTexture;
	SDL_Renderer* renderer;
	int Width, Height;
	int frameCount;
	int previousFrame;
};

#endif