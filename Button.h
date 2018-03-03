#pragma once
#include "Common.h"
#include "Component.h"
#include <functional>

class Button : public Component
{
public:
	std::vector<std::function<void()>> pointerEnter;
	std::vector<std::function<void()>> pointerExit;
	std::vector<std::function<void()>> click;
	void Update(float deltaTime);

	Button()
	{

	}
	~Button() 
	{

	};
private:
	void CallDelegate(std::vector<std::function<void()>> const& del);
protected:
	bool inBox = false;
	bool mouseDown = false;
	virtual void Clicked() { };
};