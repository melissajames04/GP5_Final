#ifndef Scene0_H
#define Scene0_H

#include "Scene.h"
#include "Window.h"

class Scene0 : public Scene
{
	enum class Action : int {
		ENTER = 1,
		QUIT,
		TOTAL
	};
public:
	explicit Scene0(class Window& windowRef);
	virtual ~Scene0();
	Scene0(const Scene0&) = delete;
	Scene0(Scene0&&) = delete;
	Scene0& operator=(const Scene0&) = delete;
	Scene0& operator=(Scene0&&) = delete;

	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float deltaTime);
	virtual void Render() const;
	void InputManager();


};

#endif
