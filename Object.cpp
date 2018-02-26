#include "Object.h"

void Object::draw(sf::RenderTarget& target) const
{
	sf::Transform combinedTransform = parent == nullptr ? transform : transform * parent->transform;

	onDraw(target, combinedTransform);
}

void Object::SetParent(Object* obj)
{
	parent = obj;
	obj->children.push_back(this);
}

Object::~Object()
{
	if (parent != nullptr) 
	{
		parent->children.erase(
			std::remove(parent->children.begin(), parent->children.end(), this), 
			parent->children.end());
	}
}
