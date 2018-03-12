#include "GameObject.h"
#include "Game.h"


GameObject::GameObject()
{
	
}

void GameObject::Init(std::string name, Textures const & textureName, sf::Vector2f position)
{
	destroyed = false;
	this->name = name;
	sf::Texture* tex = Game::resourceManager.RetrieveTexture(textureName);
	SetSprite(tex);
	SetPosition(position);
}


void GameObject::Update(float deltaTime)
{
	if (!destroyed && enabled) 
	{
		for (size_t i = 0; i < components.size(); i++)
		{
			components[i].get()->Update(deltaTime);
		}
	}
}
void GameObject::Destroy()
{
	for (size_t i = 0; i < components.size(); i++)
	{
		components[i].reset();
	}
	components.clear();
	sprite = sf::Sprite();
	fillMode = FillMode::None;
	currentTexture = nullptr;
	currentFillAmount = 1;
	Object::Destroy();
}
void GameObject::SetSprite(sf::Texture * texture, bool centered)
{
	currentTexture = texture;
	sprite.setTexture(*texture);
	if (centered) 
	{
		sf::Vector2u texSize = texture->getSize();
		sprite.setOrigin(texSize.x*0.5f, texSize.y*0.5f);
	}
	SetFillAmount(currentFillAmount);
}

void GameObject::SetFillAmount(float fillAmount)
{
	if (currentTexture == nullptr) return;
	currentFillAmount = HelperFunctions::Clamp01(fillAmount);
	unsigned int width = currentTexture->getSize().x;
	unsigned int height = currentTexture->getSize().y;
	unsigned int widthFilled = width*fillAmount;
	unsigned int heightFilled = height*fillAmount;

	switch (fillMode)
	{
	case FillMode::None:
		sprite.setTextureRect(sf::IntRect(0, 0, width, height));
		break;
	case FillMode::BottomToTop:
		sprite.setTextureRect(sf::IntRect(0, height - heightFilled, width, height));
		break;
	case FillMode::TopToBottom:
		sprite.setTextureRect(sf::IntRect(0, 0, width, heightFilled));
		break;
	case FillMode::LeftToRight:
		sprite.setTextureRect(sf::IntRect(0, 0, widthFilled, height));
		break;
	case FillMode::RightToLeft:
		sprite.setTextureRect(sf::IntRect(width - widthFilled, 0, width, height));
		break;
	default:
		break;
	}
}

