#pragma once
#include "Common.h"
#include <memory>
#include "ResourceManager.h"

class GameObject;

class ObjectManager
{
public:
	static GameObject* CreateObject(std::string _name, TextureName const & textureName, sf::Vector2f position = sf::Vector2f(0, 0));

	static void DrawObjects(sf::RenderTarget& target);

	static GameObject* Find(std::string name);
	static GameObject* Find(int id);

	static void UpdateLayerOrder();
	static void UpdateObjects(float deltaTime);

private:
	static std::vector<std::unique_ptr<GameObject>> objects;

	static bool SortByLayer(std::unique_ptr<GameObject> const & a, std::unique_ptr<GameObject> const&  b);
};

