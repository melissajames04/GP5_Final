#pragma once
#include <memory>
#include <thread>
#include "Window.h"
enum class GameState : int {
	INTRO = 0,
	LEVEL1
};
class GameSceneManager
{
private:
	GameSceneManager();
	~GameSceneManager();
	GameSceneManager(const GameSceneManager&) = delete;
	GameSceneManager(GameSceneManager&&) = delete;
	GameSceneManager& operator=(const GameSceneManager&) = delete;
	GameSceneManager& operator=(GameSceneManager&&) = delete;
	Window window;
	int fps;
	static std::unique_ptr<GameSceneManager> instance;
	friend std::default_delete < GameSceneManager >;


public:
	static GameSceneManager* getInstance();
	//static unsigned int fps;
	void Run();
	bool Initialize();
	void Update(const float deltaTime);
	bool isRunning;
	void Render(const float deltaTime);
	int testmove;
	void LoadLevel();
	static int level;
	int levelLoaded;
};



