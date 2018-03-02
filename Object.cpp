#include "Object.h"

void Object::draw(sf::RenderTarget& target)
{
	sf::Transformable combinedTransform = transform;// parent == nullptr ? this : getTransform() * parent->getTransform();
	if (parent != nullptr) 
	{
		combinedTransform.setScale(transform.getScale().x*parent->transform.getScale().x, transform.getScale().y*parent->transform.getScale().y);
		combinedTransform.setPosition(transform.getPosition().x*parent->transform.getPosition().x, transform.getPosition().y*parent->transform.getPosition().y);
		combinedTransform.setRotation(transform.getRotation()*parent->transform.getRotation());
	}
	sprite.setPosition(combinedTransform.getPosition());
	sprite.setScale(combinedTransform.getScale());
	sprite.setRotation(combinedTransform.getRotation());

	onDraw(target);
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
