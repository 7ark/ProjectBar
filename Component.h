#pragma once
#include "Common.h"

enum class Comp
{
	Animation, Button, DisplayObject, Move
};

class GameObject;

class Component
{
public:
	Component();
	virtual ~Component();
	GameObject* gameObject;
	Comp componentType;
	bool enabled = true;

	virtual void Update(float deltaTime) = 0;
};

