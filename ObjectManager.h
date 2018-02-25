#pragma once
#include "Common.h"

class GameObject;

class ObjectManager
{
public:
	static void Destroy();

	static void AddObject(GameObject* obj);

	static void DrawObjects(sf::RenderTarget& target);

private:
	static std::vector<GameObject*> objects;
};

