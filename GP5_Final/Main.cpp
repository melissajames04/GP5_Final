#include <stdio.h>
#include <thread>
#include "Window.h"
#include "GameSceneManager.h"
#include "Debug.h"
#include "GameObject.h"

GameSceneManager* gameSceneManager;
int main(int argc, char* argv[]){
	gameSceneManager = GameSceneManager::getInstance();
	std::thread mainThread(&GameSceneManager::Run, gameSceneManager);
	mainThread.join();
	mainThread.detach();
	exit(0);
}
