#include <stdio.h>
#include <thread>
#include "Window.h"
#include "GameSceneManager.h"
#include "Debug.h"
#include "GameObject.h"


//Game Programming 5 Final 

//Main is the main starting point for the program, starts up the Game Scene Manager to run the actual game
//
//GameSceneManager is made using a pointer to allow us to make it into a singleton, this will disallow us
//from making multiple GameSceneManagers throughout the game, as we only need one
//
//This program also uses threads, sending the GSM to a thread to run using join() rather than detach()
//join() runs the thread and then jumps back to the main once it's out of scope
//detach() runs the thread on it's own while still running the main program, simply ending once out of scope
//
//mainThread.detach();


using namespace std;

GameSceneManager* gameSceneManager;

int main(int argc, char* argv[]) {
	gameSceneManager = GameSceneManager::getInstance();

	thread mainThread(&GameSceneManager::Run, gameSceneManager);
	mainThread.join();

	exit(0);
}

