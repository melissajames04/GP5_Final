#include "GameSceneManager.h"
#include <iostream>
#include "Debug.h"
#include "Timer.h"
#include "GameObject.h"
#include <thread>


//The main file for the GameSceneManager, calling the various backend files like the timer and window to start creating thebase of a game
//
//INITIALIZE
//
//This section is where the game is initialized, it holds the part of the class that are normally only run once
//
//From the start, this program will create itself as a singleton so that it will only be called once, and then protect itself from being
//wrongly modified by code later on. 
//
//This starts by creating the unique_ptr and then setting it to null to get rid of any junk data that would normally be wherever it's created
//at startup.
//
//It then calls it's own getInstance and checks if it is null or not, if null then it fills it with data, if not then it simply passes it by
//
//UPDATE
//
//This section is where the game is updated, holding the parts of the class that are constantly being checked or ran by the program
//
//Here is where the GSM runs itself and starts to manage the scenes, calling it's update and render inside it's run to check if there is a
//change during the run of the program, and then to draw it while the program runs. While the GSM won't change or draw anything itself in 
//the game, it will call upon scene objects that will be created that will be updating and drawing information to the screen
//
//This will allow us to have multiple scenes that can have multiple possibilities when called, rather than being restricted by updating
//inside of the GSM itself. It will make the program much more customizable on a per game and per level basis
//
//Update can also be called into it's own little thread by calling it with //thread eventPoll(Update, 10);
//
//Input manager is where the various key commands through SDL will be stored, please note to keep any key commands within this method and 
//simply call it through InputManager()


  
//----------INITIALIZATION----------//
	GameObject* ball;

	unique_ptr<GameSceneManager> GameSceneManager::instance(nullptr);

	GameSceneManager::GameSceneManager() : window(), isRunning(false), fps(10) {
		Debug::Log(EMessageType::INFO, "Hello fomr the constructor", __FILE__, __LINE__);
	}

	GameSceneManager::~GameSceneManager() {
		window.Shutdown();

		Debug::Log(EMessageType::INFO, "Hello from the destructor", __FILE__, __LINE__);
	}

	GameSceneManager* GameSceneManager::getInstance() {
		if (instance.get() == nullptr){
			instance.reset(new GameSceneManager());
		}

		return instance.get();
	}

	bool GameSceneManager::Initialize() {
		Debug::Log(EMessageType::INFO, "Initializing", __FILE__, __LINE__);
		window.SetWindowSize(800, 600);

		if (!window.Initialize()) {
			Debug::Log(EMessageType::FATAL_ERROR, "Failed to initialize a GuI Window!", __FILE__, __LINE__);
			return false;
		}
		else {
			return true;
		}
	}




//----------UPDATING----------//
	void GameSceneManager::Run() {
		Debug::Log(EMessageType::INFO, "Running", __FILE__, __LINE__);

		isRunning = Initialize();

		Timer timer;
		timer.Start();

		Debug::Initialize();

		ball = new GameObject();
		ball->loadImage("ball.bmp");

		while (isRunning){
			timer.UpdateFrameTicks();
			Update(timer.GetDeltaTime());
			Render();
			SDL_Delay(timer.GetSleepTime(fps));
		}
	}

	void GameSceneManager::Update(const float deltaTime) {
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

	void GameSceneManager::Render() {
		SDL_RenderClear(window.GetRenderer());
		SDL_FreeSurface(window.getSurface());
		SDL_RenderCopy(window.GetRenderer(), ball->render(window.GetRenderer(), window.getSurface()), NULL, &ball->pos);
		SDL_RenderPresent(window.GetRenderer());
	}




//----------INPUT----------//
	void GameSceneManager::InputManager(SDL_Event keyEvent) {
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



