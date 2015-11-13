#include "GameSceneManager.h"
#include <iostream>
#include "Debug.h"
#include "Timer.h"
#include "GameObject.h"
#include <thread>
#include "Scene0.h"
#include "Scene1.h"
#include "InputManager.h"

//GameObject* player;
//GameObject* background;
Scene* intro;
Scene* level1;

std::unique_ptr<GameSceneManager> GameSceneManager::instance(nullptr);
GameSceneManager::GameSceneManager() : window(), isRunning(false), fps(10)
{
	Debug::Log(EMessageType::INFO, "Hello fomr the constructor", __FILE__, __LINE__);
}


GameSceneManager::~GameSceneManager()
{
	//window.Shutdown();
	Debug::Log(EMessageType::INFO, "Hello from the destructor", __FILE__, __LINE__);
}
GameSceneManager* GameSceneManager::getInstance(){
	if (instance.get() == nullptr){
		instance.reset(new GameSceneManager());
	}
	return instance.get();
}
void GameSceneManager::Run(){
	Debug::Log(EMessageType::INFO, "Running", __FILE__, __LINE__);
	isRunning = Initialize();
	Timer timer;
	timer.Start();
	Debug::Initialize();
	//player = new GameObject();
	//background = new GameObject();
	SDL_SetRenderDrawBlendMode(window.GetRenderer(), SDL_BLENDMODE_BLEND);
	//background->loadImage(window.GetRenderer(), "background.png");
	//player->loadImage(window.GetRenderer(),"guy_walk_spritesheet.png");
	//intro = new Scene0(window.GetRenderer());
	intro = new Scene0(window); 
	level1 = new Scene1(window);
	intro->OnCreate();
	level1->OnCreate();
	while (isRunning){
		timer.UpdateFrameTicks();
		//Update(timer.GetDeltaTime());
		//Render();
		//intro->Update(timer.GetDeltaTime());
		level1->Update(timer.GetDeltaTime());
		SDL_Delay(timer.GetSleepTime(fps));
	}

}
bool GameSceneManager::Initialize(){
	Debug::Log(EMessageType::INFO, "Initializing", __FILE__, __LINE__);
	window.SetWindowSize(800, 600);
	if (!window.Initialize()){
		Debug::Log(EMessageType::FATAL_ERROR, "Failed to initialize a GuI Window!", __FILE__, __LINE__);
		return false;
	}
	else{
		return true;
	}
}

void GameSceneManager::Update(const float deltaTime){
	SDL_Event SDLEvent;
	while (SDL_PollEvent(&SDLEvent)){
		switch (SDLEvent.type){
		case SDL_EventType::SDL_QUIT:
			exit(0);
			return;
			break;
		case SDL_EventType::SDL_KEYDOWN:
			InputManager(SDLEvent);
			break;
		default:
			return;
			break;
		}
	}
}

void GameSceneManager::Render(){
	SDL_RenderClear(window.GetRenderer());
	SDL_FreeSurface(window.getSurface());
	//background->Draw(0, 0, 1.0f, NULL, 0.0f, false, SDL_FLIP_NONE);
	//player->Animate(testmove, window.GetHeight() - 100, 1.0f, NULL, 0.0f, true, SDL_FLIP_NONE, 8, 0);
	SDL_RenderPresent(window.GetRenderer());
}

void GameSceneManager::InputManager(SDL_Event keyEvent){
	switch (keyEvent.key.keysym.sym){
	case SDLK_q:
		isRunning = false;
		//player = nullptr;
		//background = nullptr;
		//delete player;
		//delete background;
		SDL_Quit();
		exit(0);
		break;
	case SDLK_RIGHT:
		testmove+=10;
		break;
	default:
		break;
	}
}



