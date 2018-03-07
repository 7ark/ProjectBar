#include "GameObject.h"
#include "Game.h"


GameObject::GameObject(std::string name, Textures const & textureName, sf::Vector2f position)
{
	this->name = name;
	sf::Texture* tex = Game::resourceManager.RetrieveTexture(textureName);
	SetSprite(tex);
	SetPosition(position);
}


void GameObject::Update(float deltaTime)
{
	if (enabled) 
	{
		for (size_t i = 0; i < components.size(); i++)
		{
			components[i].get()->Update(deltaTime);
		}
	}
}
void GameObject::SetSprite(sf::Texture * texture, bool centered)
{
	sprite.setTexture(*texture);
	if (centered) 
	{
		sf::Vector2u texSize = texture->getSize();
		sprite.setOrigin(texSize.x*0.5f, texSize.y*0.5f);
	}
}

