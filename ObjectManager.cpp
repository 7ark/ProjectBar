#include "ObjectManager.h"
#include "Object.h"

std::vector<std::unique_ptr<GameObject>> ObjectManager::objects;

GameObject * ObjectManager::CreateObject(std::string _name, TextureName const & textureName, sf::Vector2f position)
{
	objects.push_back(std::make_unique<GameObject>(_name, textureName, position));
	UpdateLayerOrder();
	return objects.back().get();
}

void ObjectManager::DrawObjects(sf::RenderTarget& target)
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->draw(target);
	}
}

bool ObjectManager::SortByLayer(std::unique_ptr<GameObject> const & a, std::unique_ptr<GameObject> const&  b)
{
	return a.get()->GetLayer() < b.get()->GetLayer();
}

void ObjectManager::UpdateLayerOrder()
{
	std::sort(objects.begin(), objects.end(), SortByLayer);
}

GameObject * ObjectManager::Find(std::string name)
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		if (objects[i].get()->name == name)
			return objects[i].get();
	}
	return nullptr;
}

GameObject * ObjectManager::Find(int id)
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		if (objects[i].get()->GetUniqueID() == id)
			return objects[i].get();
	}
	return nullptr;
}


