#ifndef Scene1_H
#define Scene1_H

#include "Scene.h"
#include "Window.h"

class Scene1 : public Scene
{
	enum class Action : int {
		LEFT = 1,
		RIGHT,
		JUMP,
		QUIT,
		TOTAL
	};
public:
	explicit Scene1(class Window& windowRef);
	virtual ~Scene1();
	Scene1(const Scene1&) = delete;
	Scene1(Scene1&&) = delete;
	Scene1& operator=(const Scene1&) = delete;
	Scene1& operator=(Scene1&&) = delete;

	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float deltaTime);
	virtual void Render() const;
	void InputManager();

private:
	int moveX, speedX;
	int screenX, screenMoveX, screenX2;
	void scrollCheck();
	SDL_RendererFlip Flip;
	bool scroll;
};

#endif
