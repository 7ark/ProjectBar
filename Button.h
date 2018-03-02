#pragma once
#include "Common.h"
#include "Component.h"

class Button : public Component
{
public:
	void Update(float deltaTime);
private:
	using Callback = void();
	void CallDelegate(std::vector<Callback*> const& del);
protected:
	bool inBox = false;
	bool mouseDown = false;
	std::vector<Callback*> pointerEnter;
	std::vector<Callback*> pointerExit;
	virtual void Clicked() = 0;

	~Button() {};
};