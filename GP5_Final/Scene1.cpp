#include "Scene1.h"
#include "GameObject.h"
#include "Player.h"
#include <iostream>

Player* player;
GameObject* background;
GameObject* background2;
GameObject* groundTest;

Vec3 physicsGravity(0.0f, -1.0f, 0.0f);


Scene1::Scene1(Window& windowRef) : Scene(windowRef), moveX(0), moveY(1.5f), speedY(0), speedX(0), screenX(0), screenX2(0), screenMoveX(0), Flip(SDL_FLIP_NONE), scroll(false){
}
Scene1::~Scene1(){}

bool Scene1::OnCreate(){
	//Load Assets:
	//Background
	//Title
	//SoundEffects
	//Models for this scene
	//Music
	Matrix4 ndc = MMath::viewportNDC(window->GetWidth(), window->GetHeight());
	Matrix4 ortho = MMath::orthographic(0.0f, 10.0f, 0.0f, 8.0f, 0.0f, 10.0f);
	projection = ortho * ndc;

	player = new Player();
	background = new GameObject();
	background2 = new GameObject();
	groundTest = new GameObject();
	InputManager::initialize((int)Action::TOTAL - 1);
	InputManager::bind(SDLK_RIGHT, (int)Action::RIGHT);
	InputManager::bind(SDLK_LEFT, (int)Action::LEFT);
	InputManager::bind(SDLK_SPACE, (int)Action::JUMP);
	InputManager::bind(SDLK_q, (int)Action::QUIT);
	if (!background->loadImage(window->GetRenderer(), "background.png") ||
		!background2->loadImage(window->GetRenderer(), "background.png") ||
		!player->loadImage(window->GetRenderer(), "guy_walk_spritesheet.png") ||
		!groundTest->loadImage(window->GetRenderer(), "placeholder.png")){
		return false;
	}
	else{
		screenX2 = background->getWidth();
		return true;
	}
}

void Scene1::OnDestroy(){
	window = nullptr;
	player = nullptr;
	background = nullptr;
	background2 = nullptr;
	groundTest = nullptr;
	delete player;
	delete background;
	delete background2;
	delete groundTest;
}

void Scene1::Update(const float deltaTime){
	InputManager();
	/*if (canJump){
		if (player->position.y < 2.0f && !hitPeak)
			player->velocity.y = player->jumpVel;
		else if (moveY > 2.0f){
			hitPeak = true;
			player->velocity.y = physicsGravity.y;
		}
		else if (hitPeak){
			speedY = -0.5f;
			if (moveY <= 1.5f){
				canJump = false;
				speedY = 0;
			}
		}
	}*/

	if (player->pos.x > window->GetWidth() / 2){
		scroll = true;
		if (player->velocity.x > 0.0f)
			player->velocity.x = 0.0f;
		else
			scroll = false;
	}
	else{
			scroll = false;
	}
	
	player->position.x += player->velocity.x;
	player->position += (player->velocity * deltaTime) + 0.5f * physicsGravity * (deltaTime * deltaTime);
	player->velocity += physicsGravity * deltaTime;

	if (player->position.y <= 1.5f){
		isGrounded = true;
		canJump = true;
		physicsGravity = Vec3(0, 0, 0);
		player->velocity.y = 0.0f;
		player->position.y = 1.5f;
	}
	else {
		isGrounded = false;
		canJump = false;
		physicsGravity = Vec3(0, -1.0f, 0);
	}


	player->position.y += speedY;
	screenX += screenMoveX;
	screenX2 += screenMoveX;
	scrollCheck();
	Render();

}

void Scene1::Render() const{
	Vec3 screenCoords = projection * Vec3(player->position.x, player->position.y, 0);
	Vec3 groundCoords = projection * Vec3(0, 0.34f, 0);
	window->ClearRenderer();
	SDL_FreeSurface(window->getSurface());
	//Draw the scene:
	background->Draw(screenX, 0, 1.0f, NULL, 0.0f, false, SDL_FLIP_NONE);
	background2->Draw(screenX2 , 0, 1.0f, NULL, 0.0f, false, SDL_FLIP_HORIZONTAL);
	groundTest->Draw(groundCoords.x, groundCoords.y, 1.0f, NULL, 0.0f, true, SDL_FLIP_NONE);
	player->Animate(screenCoords.x, screenCoords.y, 1.0f, NULL, 0.0f, true, Flip, 8);
	SDL_RenderPresent(window->GetRenderer());
}

void Scene1::scrollCheck(){
	if (player->pos.x > window->GetHeight() / 2 && scroll)
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
	if (isGrounded){
		if (action == (int)Action::LEFT){
			Flip = SDL_FLIP_HORIZONTAL;
			player->velocity.x = -0.2f;
		}
		else if (action == (int)Action::RIGHT){
			Flip = SDL_FLIP_NONE;
			player->velocity.x = 0.2f;
		}
		else
		{
			player->velocity.x = 0.0f;
		}
	}
	//if(action == -1){
	//	speedX = 0;
	//	scroll = false;
	//}
	if (action == (int)Action::JUMP){
		if (isGrounded)
			player->velocity.y += player->jumpVel;
	}

	if (action == (int)Action::QUIT){
		SDL_Quit();
		exit(0);
	}

}


