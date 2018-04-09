#include "Object.h"

int Object::globalId = 0;

void Object::Draw(sf::RenderTarget& target)
{
	if (destroyed) return;
	sf::Transformable combinedTransform = transform;
	if (parent != nullptr)
	{
		combinedTransform.setScale(GetLocalScale());
		combinedTransform.setPosition(GetLocalPosition());
		combinedTransform.setRotation(GetLocalRotation());
	}
	OnDraw(target, combinedTransform);
}

sf::Vector2f Object::GetLocalPosition()
{
	if (parent == nullptr) 
	{
		std::cout << "ERROR: Tried to get the local position of an object with no parent";
		return sf::Vector2f(0, 0);
	}
	return transform.getPosition() + (parent->parent == nullptr ? parent->transform.getPosition() : parent->GetLocalPosition());
}

sf::Vector2f Object::GetLocalScale()
{
	if (parent == nullptr)
	{
		std::cout << "ERROR: Tried to get the local scale of an object with no parent";
		return sf::Vector2f(0, 0);
	}
	return sf::Vector2f(
		transform.getScale().x * (parent->parent == nullptr ? parent->transform.getScale().x : parent->GetLocalScale().x), 
		transform.getScale().y * (parent->parent == nullptr ? parent->transform.getScale().y : parent->GetLocalScale().y));
}

float Object::GetLocalRotation()
{
	if (parent == nullptr)
	{
		std::cout << "ERROR: Tried to get the local rotation of an object with no parent";
		return 0;
	}
	return transform.getRotation() + (parent->parent == nullptr ? parent->transform.getRotation() : parent->GetLocalRotation());
}

void Object::SetParent(Object* obj, bool adjustToLocal)
{
	if (destroyed) return;
	if (obj == nullptr)
	{
		if (adjustToLocal) 
		{
			SetPosition(parent->GetPosition() + GetPosition());
			SetScale(sf::Vector2f(GetScale().x * parent->GetScale().x, GetScale().y * parent->GetScale().y));
		}
		parent->children.erase(
			std::remove(parent->children.begin(), parent->children.end(), this),
			parent->children.end());
		parent = nullptr;
	}
	else
	{
		parent = obj;
		obj->children.push_back(this);
		if (adjustToLocal)
		{
			sf::Vector2f diff = GetPosition() - parent->GetPosition();
			SetPosition(diff);
			sf::Vector2f parentScale = parent->GetScale();
			sf::Vector2f scaleDiff = sf::Vector2f(GetScale().x / parentScale.x, GetScale().y / parentScale.y);
			SetScale(scaleDiff);
		}
	}
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
