#pragma once
#include "Common.h"
#include <memory>
#include "ResourceManager.h"

class GameObject;

class ObjectManager
{
public:
	static GameObject* CreateObject(TextureName const & name, sf::Vector2f position = sf::Vector2f(0, 0));

	static void DrawObjects(sf::RenderTarget& target);

private:
	static std::vector<std::unique_ptr<GameObject>> objects;
};

