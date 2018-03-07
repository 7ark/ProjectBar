#include "ObjectManager.h"
#include "GameObject.h"
#include "Text.h"
#include "Object.h"

std::vector<std::unique_ptr<Object>> ObjectManager::objects;

GameObject * ObjectManager::CreateObject(std::string _name, Scenes view, Textures const & textureName, sf::Vector2f position)
{
	objects.push_back(std::make_unique<GameObject>(_name, textureName, position));
	GameObject* result = static_cast<GameObject*>(objects.back().get());
	result->SetScene(view);
	UpdateLayerOrder();
	return result;
}

Text * ObjectManager::CreateText(std::string name, Scenes view, Fonts const & fontName, sf::String txt, sf::Vector2f position)
{
	objects.push_back(std::make_unique<Text>(name, fontName, txt, position));
	Text* result = static_cast<Text*>(objects.back().get());
	result->SetScene(view);
	UpdateLayerOrder();
	return result;
}

void ObjectManager::Destroy(const GameObject* obj)
{

}

void ObjectManager::DrawObjects(sf::RenderTarget& target, Scenes view)
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		Scenes current = objects[i]->GetScene();
		if((current == Scenes::SceneAll && view != Scenes::UI) || current == view)
			objects[i]->draw(target);
	}
}

Object * ObjectManager::Find(std::string name)
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		if (objects[i].get()->name == name)
			return objects[i].get();
	}
	return nullptr;
}

Object * ObjectManager::Find(int id)
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		if (objects[i].get()->GetUniqueID() == id)
			return objects[i].get();
	}
	return nullptr;
}

bool ObjectManager::SortByLayer(std::unique_ptr<Object> const & a, std::unique_ptr<Object> const&  b)
{
	return a.get()->GetLayer() < b.get()->GetLayer();
}

void ObjectManager::UpdateLayerOrder()
{
	std::sort(objects.begin(), objects.end(), SortByLayer);
}

void ObjectManager::UpdateObjects(float deltaTime)
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i].get()->Update(deltaTime);
	}
}


