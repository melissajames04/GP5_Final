#include "Scene0.h"
#include "GameObject.h"

GameObject* splashScreen;

Scene0::Scene0(Window& windowRef) : Scene(windowRef){
}
Scene0::~Scene0(){}

bool Scene0::OnCreate(){
	//Load Assets:
	//Background
	//Title
	//SoundEffects
	//Models for this scene
	//Music
	splashScreen = new GameObject();
	splashScreen->loadImage(window->GetRenderer(), "limbo_title.bmp");
	InputManager::initialize((int)Action::TOTAL - 1);
	InputManager::bind(SDLK_RETURN, (int)Action::ENTER);
	InputManager::bind(SDLK_q, (int)Action::QUIT);
	return true;
}

void Scene0::OnDestroy(){
	window = nullptr;
	splashScreen = nullptr;
	delete splashScreen;
}

void Scene0::Update(const float deltaTime){
	InputManager();
		Render();
}

void Scene0::Render() const{
	window->ClearRenderer();
	SDL_FreeSurface(window->getSurface());
	//Draw the scene:
	splashScreen->Draw(0, 0, 1.0f, NULL, 0.0f, false, SDL_FLIP_NONE);
	SDL_RenderPresent(window->GetRenderer());
}

void Scene0::InputManager(){
	int action = InputManager::Update();
	switch (action){
	case (int)Action::ENTER:
		GameSceneManager::level = 1;
		break;
	case(int)Action::QUIT:
		SDL_Quit();
		exit(0);
		break;
	default:
		break;
	}
}