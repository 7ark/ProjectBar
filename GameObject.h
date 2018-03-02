#pragma once
#include "Common.h"
#include "ObjectManager.h"
#include "Object.h"

#include "Component.h"

class Game;

class GameObject : public Object
{
public:
	GameObject(std::string _name, Textures const & textureName, sf::Vector2f position = sf::Vector2f(0, 0));

	void Update(float deltaTime);

	//Getters
	sf::Sprite GetSprite() { return sprite; }

	//Setters
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

protected:
	sf::Sprite sprite;

	std::vector<std::unique_ptr<Component>> components;

	virtual void onDraw(sf::RenderTarget& target, sf::Transformable& transform)
	{
		sprite.setPosition(transform.getPosition());
		sprite.setScale(transform.getScale());
		sprite.setRotation(transform.getRotation());
		target.draw(sprite);
	}
};


