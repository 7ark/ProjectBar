#pragma once
#include "Common.h"
#include "ObjectManager.h"
#include "Object.h"

#include "Component.h"

class Game;

class GameObject : public Object
{
public:
	GameObject();
	void Init(std::string name, Textures const & textureName, sf::Vector2f position = sf::Vector2f(0, 0));

	void Update(float deltaTime);
	void Destroy();

	//Getters
	sf::Sprite GetSprite() { return sprite; }
	sf::Texture* GetSpriteTexture() { return currentTexture; }
	sf::Color GetColor() { return sprite.getColor(); }
	FillMode GetFillMode() { return fillMode; }
	float GetFillAmount() { return currentFillAmount; }

	//Setters
	void SetSprite(sf::Texture* texture, bool centered = true);
	void SetColor(sf::Color color) { sprite.setColor(color); }
	void SetFillMode(FillMode mode) { fillMode = mode; }
	void SetFillAmount(float fillAmount);
	void ChangeFillAmount(float amount) { SetFillAmount(currentFillAmount + amount); }

	template<class T>
	T* AddComponent(Comp componentType)
	{
		components.push_back(std::make_unique<T>());
		Component* result = components.back().get();
		result->gameObject = this;
		result->componentType = componentType;
		return (T*)result;
	}

	template<class T>
	T* GetComponent(Comp componentType)
	{
		for (size_t i = 0; i < components.size(); i++)
		{
			if (components[i].get()->componentType == componentType)
				return (T*)components[i].get();
		}
		return nullptr;
	}

	template<class T>
	std::vector<T*> GetComponents(Comp componentType)
	{
		std::vector<T*> result;
		for (size_t i = 0; i < components.size(); i++)
		{
			if (components[i].get()->componentType == componentType)
				result.push_back((T*)components[i].get());
		}
		return result;
	}

protected:
	sf::Sprite sprite;
	sf::Texture* currentTexture;
	FillMode fillMode = FillMode::None;
	float currentFillAmount = 1;

	std::vector<std::unique_ptr<Component>> components;

	virtual void onDraw(sf::RenderTarget& target, sf::Transformable& transform)
	{
		float xScale = transform.getScale().x;
		float yScale = transform.getScale().y;
		float xPosition = (fillMode == FillMode::RightToLeft ? (currentTexture->getSize().x * xScale) *(1 - currentFillAmount) : 0);
		float yPosition = (fillMode == FillMode::BottomToTop ? (currentTexture->getSize().y * yScale) *(1 - currentFillAmount) : 0);

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


		sprite.setPosition(sf::Vector2f(xPosition,yPosition));
		sprite.setScale(sf::Vector2f(xScale,yScale));
		sprite.setRotation(transform.getRotation());
		if(enabled && visible)
			target.draw(sprite);
	}
};


