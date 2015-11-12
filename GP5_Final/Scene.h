#ifndef SCENE_H
#define SCENE_H

#include "SDL.h"
#include "Window.h"

class Scene
{
public:
	explicit Scene(class Window& windowRef);
	virtual ~Scene();
	Scene(const Scene&) = delete;
	Scene(Scene&&) = delete;
	Scene& operator = (const Scene&) = delete;
	Scene& operator = (Scene&&) = delete;

	//Create the following 4 abstract function (polymorphically)
	//proper term: pure virtuals
	virtual bool OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Update(const float deltaTime) = 0;
	virtual void Render() const = 0;

protected:
	Window * window;
};

#endif
