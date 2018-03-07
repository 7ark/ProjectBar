#pragma once
#include "Common.h"
#include <memory>
#include "ResourceManager.h"

class Object;
class GameObject;
class Text;

class ObjectManager
{
public:
	static GameObject* CreateObject(std::string _name, Scenes view, Textures const & textureName, sf::Vector2f position = sf::Vector2f(0, 0));
	static Text* CreateText(std::string name, Scenes view, Fonts const & fontName, sf::String txt = "", sf::Vector2f position = sf::Vector2f(0, 0));

	static void Destroy(const GameObject* obj);

	static void DrawObjects(sf::RenderTarget& target, Scenes view);

	static Object* Find(std::string name);
	static Object* Find(int id);

	static void UpdateLayerOrder();
	static void UpdateObjects(float deltaTime);

private:
	static std::vector<std::unique_ptr<Object>> objects;

	static bool SortByLayer(std::unique_ptr<Object> const & a, std::unique_ptr<Object> const&  b);
};

