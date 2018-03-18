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
	material = Material();
	currentFillAmount = 1;
	Object::Destroy();
}
void GameObject::SetSprite(sf::Texture * texture, bool centered)
{
	material.SetTexture(texture);
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
	if (material.GetTexture() == nullptr) return;
	currentFillAmount = HelperFunctions::Clamp01(fillAmount);
	unsigned int width = material.GetTexture()->getSize().x;
	unsigned int height = material.GetTexture()->getSize().y;
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

void GameObject::OnDraw(sf::RenderTarget & target, sf::Transformable & transform)
{
	float xScale = transform.getScale().x;
	float yScale = transform.getScale().y;
	float xPosition = (fillMode == FillMode::RightToLeft ? (material.GetTexture()->getSize().x * xScale) *(1 - currentFillAmount) : 0);
	float yPosition = (fillMode == FillMode::BottomToTop ? (material.GetTexture()->getSize().y * yScale) *(1 - currentFillAmount) : 0);

	xPosition += transform.getPosition().x;
	yPosition += transform.getPosition().y;

	if (scene == Scenes::UI)
	{
		float xRatio = xPosition / GameSettings::uiReferenceWidthHalf;
		float yRatio = yPosition / GameSettings::uiReferenceHeightHalf;
		float xRatioCorrect = xPosition / GameSettings::resolutionWidthHalf;
		float yRatioCorrect = yPosition / GameSettings::resolutionHeightHalf;
		xRatio = xRatio - xRatioCorrect;
		yRatio = yRatio - yRatioCorrect;

		xPosition += GameSettings::resolutionWidthHalf*xRatio;
		yPosition += GameSettings::resolutionHeightHalf*yRatio;
		xScale *= xRatio + 1;
		yScale *= xRatio + 1;
	}


	sprite.setPosition(sf::Vector2f(xPosition, yPosition));
	sprite.setScale(sf::Vector2f(xScale, yScale));
	sprite.setRotation(transform.getRotation());

	material.BindShader();

	if (enabled && visible) 
	{
		target.draw(sprite, material.GetShader());
	}
}

