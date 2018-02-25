#pragma once
#include "Common.h"
#include "Game.h"
#include "ObjectManager.h"

class Object
{
public:
	sf::Transform transform;

	void draw(sf::RenderTarget& target) const
	{
		sf::Transform combinedTransform = parent == nullptr ? transform : transform * parent->transform;

		onDraw(target, combinedTransform);
	}

	void SetParent(Object* obj)
	{
		parent = obj;
		obj->children.push_back(this);
	}

	std::vector<Object*> GetChildren() const
	{
		return children;
	}

private:

	virtual void onDraw(sf::RenderTarget& target, const sf::Transform& transform) const = 0;

	Object* parent = nullptr;
	std::vector<Object*> children;

protected:
	~Object()
	{
		if(parent != nullptr)
			delete parent;
	}
};

class GameObject : public Object
{
public:
	std::string name;

	GameObject(std::string _name, TextureName const & textureName, sf::Vector2f position = sf::Vector2f(0, 0));

	int GetUniqueID() { return id; }
	void SetLayer(int l) { layer = l; ObjectManager::UpdateLayerOrder(); }
	int GetLayer() { return layer; }

private:
	sf::Sprite sprite;
	static int globalId;
	int id;
	unsigned int layer = 0;

	void NewID()
	{
		id = ++globalId;
	}

	virtual void onDraw(sf::RenderTarget& target, const sf::Transform& transform) const
	{
		target.draw(sprite, transform);
	}
};