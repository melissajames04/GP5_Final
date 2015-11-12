#include "Scene1.h"
#include "GameObject.h"

GameObject* player;
GameObject* background;

Scene1::Scene1(Window& windowRef) : Scene(windowRef){
}
Scene1::~Scene1(){}

bool Scene1::OnCreate(){
	//Load Assets:
	//Background
	//Title
	//SoundEffects
	//Models for this scene
	//Music
	testmove = 0;
	player = new GameObject();
	background = new GameObject();
	background->loadImage(window->GetRenderer(), "background.png");
	player->loadImage(window->GetRenderer(), "guy_walk_spritesheet.png");
	return true;
}

void Scene1::OnDestroy(){
	window = nullptr;
	player = nullptr;
	background = nullptr;
	delete player;
	delete background;
}

void Scene1::Update(const float deltaTime){
	InputManager();
	Render();
}

void Scene1::Render() const{
	window->ClearRenderer();
	SDL_FreeSurface(window->getSurface());
	//Draw the scene:
	background->Draw(0, 0, 1.0f, NULL, 0.0f, false, SDL_FLIP_NONE);
	player->Animate(testmove, window->GetHeight() - 100, 1.0f, NULL, 0.0f, true, SDL_FLIP_NONE, 8, 0);
	SDL_RenderPresent(window->GetRenderer());
}

void Scene1::InputManager(){
	SDL_Event SDLEvent;
	while (SDL_PollEvent(&SDLEvent)){
		switch (SDLEvent.key.keysym.sym){
		case SDLK_RIGHT:
			testmove += 10;
			break;
		default:
			return;
			break;
		}
	}
}
