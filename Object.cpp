#include "Object.h"


int GameObject::globalId = 0;

GameObject::GameObject(std::string _name, TextureName const & textureName, sf::Vector2f position)
{
	name = _name;
	sf::Texture* tex = Game::resourceManager.RetrieveTexture(textureName);
	sprite.setTexture(*tex);
	sf::Vector2u texSize = tex->getSize();
	sprite.setOrigin(texSize.x*0.5f, texSize.y*0.5f);
	sprite.setPosition(position);

	NewID();
}
