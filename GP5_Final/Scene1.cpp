#include "Scene1.h"
#include "GameObject.h"
#include <iostream>
GameObject* player;
GameObject* background;
GameObject* background2;

Scene1::Scene1(Window& windowRef) : Scene(windowRef), moveX(0), speedX(0), screenX(0), screenX2(0), screenMoveX(0), Flip(SDL_FLIP_NONE), scroll(false){
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
	background2 = new GameObject();
	background->loadImage(window->GetRenderer(), "background.png");
	background2->loadImage(window->GetRenderer(), "background.png");
	player->loadImage(window->GetRenderer(), "guy_walk_spritesheet.png");
	screenX2 = background->getWidth();
	InputManager::initialize((int)Action::TOTAL - 1);
	InputManager::bind(SDLK_RIGHT, (int)Action::RIGHT);
	InputManager::bind(SDLK_LEFT, (int)Action::LEFT);
	InputManager::bind(SDLK_q, (int)Action::QUIT);
	return true;
}

void Scene1::OnDestroy(){
	window = nullptr;
	player = nullptr;
	background = nullptr;
	background2 = nullptr;
	delete player;
	delete background;
	delete background2;
}

void Scene1::Update(const float deltaTime){
	InputManager();
	moveX += speedX;
	screenX += screenMoveX;
	screenX2 += screenMoveX;
	scrollCheck();
	Render();

}

void Scene1::Render() const{
	window->ClearRenderer();
	SDL_FreeSurface(window->getSurface());
	//Draw the scene:
	background->Draw(screenX, 0, 1.0f, NULL, 0.0f, false, SDL_FLIP_NONE);
	background2->Draw(screenX2 , 0, 1.0f, NULL, 0.0f, false, SDL_FLIP_HORIZONTAL);
	player->Animate(moveX, window->GetHeight() - 100,1.0f, NULL, 0.0f, true, Flip, 8);
	SDL_RenderPresent(window->GetRenderer());
}

void Scene1::scrollCheck(){
	if (moveX > window->GetHeight() / 2 && scroll)
		screenMoveX = -10;
	else
		screenMoveX = 0;

	if (screenX <= -background->getWidth())
		screenX = background->getWidth();
	if (screenX2 <= -background2->getWidth())
		screenX2 = background->getWidth();
}

void Scene1::InputManager(){
	int action = InputManager::Update();
	string temp = string("right");
	switch (action){
	case (int)Action::LEFT:
		scroll = false;
		Flip = SDL_FLIP_HORIZONTAL;
		speedX = -10;
		break;
	case(int)Action::RIGHT:
		Flip = SDL_FLIP_NONE;
		if (player->pos.x > window->GetWidth() / 2){
			scroll = true;
			speedX = 0;
		}
		else{
			scroll = false;
			speedX = 10;
		}
		break;
	case(int)Action::QUIT:
		SDL_Quit();
		exit(0);
		break;
	default:
		speedX = 0;
		scroll = false;
		break;
	}
}


