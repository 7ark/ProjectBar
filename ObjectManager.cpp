#include "ObjectManager.h"
#include "Object.h"

std::vector<std::unique_ptr<GameObject>> ObjectManager::objects;

GameObject * ObjectManager::CreateObject(TextureName const & name, sf::Vector2f position)
{
	objects.push_back(std::make_unique<GameObject>(name, position));
	return objects.back().get();
}

void ObjectManager::DrawObjects(sf::RenderTarget& target)
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->draw(target);
	}
}
