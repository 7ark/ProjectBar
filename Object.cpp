#include "Object.h"

int Object::globalId = 0;

void Object::draw(sf::RenderTarget& target)
{
	if (enabled && visible)
	{
		sf::Transformable combinedTransform = transform;
		if (parent != nullptr)
		{
			combinedTransform.setScale(transform.getScale().x*parent->transform.getScale().x, transform.getScale().y*parent->transform.getScale().y);
			combinedTransform.setPosition(transform.getPosition().x*parent->transform.getPosition().x, transform.getPosition().y*parent->transform.getPosition().y);
			combinedTransform.setRotation(transform.getRotation()*parent->transform.getRotation());
		}

		onDraw(target, combinedTransform);
	}
}

void Object::SetParent(Object* obj)
{
	parent = obj;
	obj->children.push_back(this);
}

Object::Object()
{
	NewID();
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
