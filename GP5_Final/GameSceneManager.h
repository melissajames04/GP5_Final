#pragma once
#include <memory>
#include <thread>
#include "Window.h"


//GameSceneManager is where the game itself will be managed and updated. After initializing all of the backend classes, it updates and 
//renders everything that will be in the game, calling the current scenes
//This allows us to add things like a timestamp, physics, window modifier, and images or game objects to render whenever we add something new
//
//Create a window object to be used to control the size of the window, as well as what it displays before rendering images
//
//We also create the variables to hold the games set fps and whether it's running or not
//
//The static unique pointer is used to create a smart pointer that will delete itself once out of scope, while the friend function
//allows us to see into GameSceneManager's privates and use unique_ptr's default_delete to delete the object when out of scope
//
//In the public space we declare the getInstance to be static, which is part of our steps to making the GSM a singleton,
//again we keep it static so as it's made when compiled so we can check if there's a GSM or not right away
//
//Grouped together are the various methods in the main GSM file, these are what we will be using to control the flow of data in our game
//
//The series of deletes are used to delete the basic constructors that VS tries to make for you when compiling 


using namespace std;

class GameSceneManager
{
	private:
		GameSceneManager();
		~GameSceneManager();
	
		Window window;

		unsigned int fps;
		bool isRunning;
	
		static unique_ptr<GameSceneManager> instance;
		friend default_delete < GameSceneManager >;


	public:
		static GameSceneManager* getInstance();

		void Run();
		bool Initialize();
		void Update(const float deltaTime);		
		void Render();
		void InputManager(SDL_Event keyEvent);

		GameSceneManager(const GameSceneManager&) = delete;
		GameSceneManager(GameSceneManager&&) = delete;
		GameSceneManager& operator=(const GameSceneManager&) = delete;
		GameSceneManager& operator=(GameSceneManager&&) = delete;
};



