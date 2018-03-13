#include "Object.h"

int Object::globalId = 0;

void Object::Draw(sf::RenderTarget& target)
{
	if (destroyed) return;
	sf::Transformable combinedTransform = transform;
	if (parent != nullptr)
	{
		combinedTransform.setScale(transform.getScale().x*parent->transform.getScale().x, transform.getScale().y*parent->transform.getScale().y);
		combinedTransform.setPosition(transform.getPosition() + parent->transform.getPosition());
		combinedTransform.setRotation(transform.getRotation() + parent->transform.getRotation());
	}
	OnDraw(target, combinedTransform);
}

void Object::SetParent(Object* obj)
{
	if (destroyed) return;
	parent = obj;
	obj->children.push_back(this);
}

Object::Object()
{
	NewID();
}

void Object::Destroy()
{
	DeleteObject();
	destroyed = true;
	enabled = true;
	visible = true;
	transform = sf::Transformable();
	ObjectManager::objectsInPool.push_back(this);
}

void Object::DeleteObject()
{
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->parent = nullptr;
	}
	if (parent != nullptr)
	{
		parent->children.erase(
			std::remove(parent->children.begin(), parent->children.end(), this),
			parent->children.end());
	}
}

Object::~Object()
{
	DeleteObject();
}
