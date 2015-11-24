#include "GameSceneManager.h"
#include <iostream>
#include "Debug.h"
#include "Timer.h"
#include "GameObject.h"
#include <thread>
#include "Scene0.h"
#include "Scene1.h"
#include "InputManager.h"

Scene* currentLevel;
//Scene* level1;
int GameSceneManager::level = 0;
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
	SDL_SetRenderDrawBlendMode(window.GetRenderer(), SDL_BLENDMODE_BLEND);
	while (isRunning){
		timer.UpdateFrameTicks();
		Update(timer.GetDeltaTime());
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
		level = (int)GameState::INTRO;
		LoadLevel();
		return true;
	}
}

void GameSceneManager::LoadLevel(){
	switch (level){
	case ((int)GameState::INTRO) :
		currentLevel = new Scene0(window);
		levelLoaded = level;
		break;
	case((int)GameState::LEVEL1) :
		currentLevel->OnDestroy();
		InputManager::clearBinds();
		currentLevel = new Scene1(window);
		levelLoaded = level;
		break;
	}
	currentLevel->OnCreate();
}
void GameSceneManager::Update(const float deltaTime){
	if (level != levelLoaded)
		LoadLevel();
	Render(deltaTime);
}

void GameSceneManager::Render(const float deltaTime){
	currentLevel->Update(deltaTime);
}




