#include "ObjectManager.h"
#include "Object.h"

std::vector<GameObject*> ObjectManager::objects;

void ObjectManager::Destroy()
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		delete objects[i];
	}
}

void ObjectManager::AddObject(GameObject* obj)
{
	objects.push_back(obj);
}

void ObjectManager::DrawObjects(sf::RenderTarget& target)
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->draw(target);
	}
}
