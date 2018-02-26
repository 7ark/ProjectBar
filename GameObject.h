#pragma once
#include "Common.h"
#include "ObjectManager.h"
#include "Object.h"

#include "Component.h"

class Game;

class GameObject : public Object
{
public:
	std::string name = "Null";

	GameObject(std::string _name, TextureName const & textureName, sf::Vector2f position = sf::Vector2f(0, 0));

	void Update(float deltaTime);

	//Getters
	int GetUniqueID() { return id; }
	int GetLayer() { return layer; }

	//Setters
	void SetLayer(int l) { layer = l; ObjectManager::UpdateLayerOrder(); }
	void SetSprite(sf::Texture* texture, bool centered = true);

	template<class T>
	T* AddComponent(Comp componentType)
	{
		components.push_back(std::make_unique<T>());
		Component* result = components.back().get();
		result->gameObject = this;
		result->componentType = componentType;
		return (T*)result;
	}

	template<class T>
	T* GetComponent(Comp componentType)
	{
		for (size_t i = 0; i < components.size(); i++)
		{
			if (components[i].get()->componentType == componentType)
				return (T*)components[i].get();
		}
		return nullptr;
	}

private:
	sf::Sprite sprite;
	static int globalId;
	int id = 0;
	int layer = 0;
	std::vector<std::unique_ptr<Component>> components;

	void NewID() { id = ++globalId; }

	virtual void onDraw(sf::RenderTarget& target, const sf::Transform& transform) const
	{
		target.draw(sprite, transform);
	}
};


