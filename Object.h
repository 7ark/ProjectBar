#pragma once
#include "Common.h"

class Object
{
public:

	void draw(sf::RenderTarget& target);

	void SetParent(Object* obj);

	const std::vector<Object*>& GetChildren() const
	{
		return children;
	}

	void SetPosition(sf::Vector2f pos) { transform.setPosition(pos.x, -pos.y); }
	void Translate(sf::Vector2f pos) { transform.move(pos); }
	void SetScale(sf::Vector2f scale) { transform.setScale(scale); }
	void Scale(sf::Vector2f scale) { transform.scale(scale); }
	void SetRotation(float angle) { transform.setRotation(angle); }
	void Rotate(float angle) { transform.rotate(angle); }

protected:
	sf::Sprite sprite;

	sf::Transformable transform;

	virtual void onDraw(sf::RenderTarget& target) const = 0;

	Object* parent = nullptr;
	std::vector<Object*> children;

	~Object();
};

