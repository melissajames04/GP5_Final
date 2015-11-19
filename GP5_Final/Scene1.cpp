#include "Scene1.h"
#include "GameObject.h"
#include "InputManager.h"
#include <iostream>
GameObject* player;
GameObject* background;

Scene1::Scene1(Window& windowRef) : Scene(windowRef), moveX(0), speedX(0), Flip(SDL_FLIP_NONE){
}
Scene1::~Scene1(){}

bool Scene1::OnCreate(){
	//Load Assets:
	//Background
	//Title
	//SoundEffects
	//Models for this scene
	//Music
	player = new GameObject();
	background = new GameObject();
	background->loadImage(window->GetRenderer(), "background.png");
	player->loadImage(window->GetRenderer(), "guy_walk_spritesheet.png");
	InputManager::initialize(1);
	InputManager::bind(SDLK_RIGHT, (int)Action::RIGHT);
	InputManager::bind(SDLK_LEFT, (int)Action::LEFT);
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
	moveX += speedX;
	Render();
}

void Scene1::Render() const{
	window->ClearRenderer();
	SDL_FreeSurface(window->getSurface());
	//Draw the scene:
	background->Draw(0, 0, 1.0f, NULL, 0.0f, false, SDL_FLIP_NONE);
	
	player->Animate(moveX, window->GetHeight() - 100,1.0f, NULL, 0.0f, true, Flip, 8);
	SDL_RenderPresent(window->GetRenderer());
}

void Scene1::InputManager(){
	int action = InputManager::Update();
	string temp = string("right");
	switch (action){
	case (int)Action::LEFT:
		Flip = SDL_FLIP_HORIZONTAL;
		speedX = -10;
		break;
	case(int)Action::RIGHT:
		Flip = SDL_FLIP_NONE;
		speedX = 10;
		break;
	default:
		speedX = 0;
		break;
	}
}


