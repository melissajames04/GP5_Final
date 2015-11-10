#include "GameSceneManager.h"
#include <iostream>
#include "Debug.h"
#include "Timer.h"
#include "GameObject.h"
#include <thread>



GameObject* ball;

std::unique_ptr<GameSceneManager> GameSceneManager::instance(nullptr);
GameSceneManager::GameSceneManager() : window(), isRunning(false), fps(10)
{
	Debug::Log(EMessageType::INFO, "Hello fomr the constructor", __FILE__, __LINE__);
}


GameSceneManager::~GameSceneManager()
{
	window.Shutdown();
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
	ball = new GameObject();
	ball->loadImage(window.GetRenderer(),"boy.png");
	//std::thread eventPoll(Update, 10);
	while (isRunning){
		timer.UpdateFrameTicks();
		Update(timer.GetDeltaTime());
		Render();
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
	//SDL_RenderCopy(window.GetRenderer(), ball->render(window.GetRenderer()), NULL, &ball->pos);
	//SDL_RenderCopyEx(window.GetRenderer(), ball->render(window.GetRenderer()), NULL, &ball->pos, 0.0f, new SDL_Point{ 0.0f, 0.0f }, SDL_FLIP_NONE);
	ball->render2(window.GetRenderer(), window.getSurface());
	SDL_RenderPresent(window.GetRenderer());
}

void GameSceneManager::InputManager(SDL_Event keyEvent){
	switch (keyEvent.key.keysym.sym){
	case SDLK_q:
		isRunning = false;
		ball = nullptr;
		delete ball;
		SDL_Quit();
		exit(0);
		break;
	default:
		break;
	}
}



