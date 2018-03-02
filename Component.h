#pragma once
#include "Common.h"

enum class Comp
{
	Animation, Button, JournalDisplay
};

class GameObject;

class Component
{
public:
	Component();
	virtual ~Component();
	GameObject* gameObject;
	Comp componentType;

	virtual void Update(float deltaTime) = 0;
};

