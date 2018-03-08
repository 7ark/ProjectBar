#pragma once
#include "Common.h"
#include "Component.h"
#include "GameObject.h"

class Move : public Component
{
public:
	Move();
	~Move();

	void LerpTo(sf::Vector2f position, float time);
	void LerpTo(sf::Vector2f position, sf::Vector2f scale, float time);

	void Update(float deltaTime);

private:

	sf::Vector2f originalPosition;
	sf::Vector2f targetPosition;
	sf::Vector2f originalScale;
	sf::Vector2f targetScale;
	float timeToMove = 0;
	float timeProgressed = 0;
	bool moving = false;
	bool scaling = false;
};

