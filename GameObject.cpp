#include "GameObject.h"
#include "Game.h"

int GameObject::globalId = 0;

GameObject::GameObject(std::string _name, TextureName const & textureName, sf::Vector2f position)
{
	name = _name;
	sf::Texture* tex = Game::resourceManager.RetrieveTexture(textureName);
	SetSprite(tex);
	position.y = -position.y;
	sprite.setPosition(position);
	NewID();
}

void GameObject::Update(float deltaTime)
{
	for (size_t i = 0; i < components.size(); i++)
	{
		components[i].get()->Update(deltaTime);
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
