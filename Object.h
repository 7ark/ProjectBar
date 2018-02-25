#pragma once
#include "Common.h"

class Object
{
public:
	sf::Transform transform;

	void draw(sf::RenderTarget& target) const;

	void SetParent(Object* obj);

	std::vector<Object*> GetChildren() const
	{
		return children;
	}

private:

	virtual void onDraw(sf::RenderTarget& target, const sf::Transform& transform) const = 0;

	Object* parent = nullptr;
	std::vector<Object*> children;

protected:
	~Object();
};

