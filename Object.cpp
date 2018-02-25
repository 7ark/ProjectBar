#include "Object.h"


int GameObject::globalId = 0;

GameObject::GameObject(TextureName const & name, sf::Vector2f position)
{
	sf::Texture* tex = Game::resourceManager.RetrieveTexture(name);
	sprite.setTexture(*tex);
	sf::Vector2u texSize = tex->getSize();
	sprite.setOrigin(texSize.x*0.5f, texSize.y*0.5f);
	sprite.setPosition(position);

	NewID();
}
