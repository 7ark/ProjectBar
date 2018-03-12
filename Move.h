#pragma once
#include "Common.h"
#include "Component.h"
#include "GameObject.h"
#include <functional>

class Move : public Component
{
public:
	Move();
	~Move();

	void LerpTo(sf::Vector2f position, float time, std::function<void()> callback = nullptr);
	void LerpTo(sf::Vector2f position, sf::Vector2f scale, float time, std::function<void()> callback = nullptr);
	void LerpTo(sf::Vector2f position, float rotation, float time, std::function<void()> callback = nullptr);

	void Update(float deltaTime);

private:
	std::function<void()> currentCallback = nullptr;
	sf::Vector2f originalPosition;
	sf::Vector2f targetPosition;
	sf::Vector2f originalScale;
	sf::Vector2f targetScale;
	float originalRotation;
	float targetRotation;

	float timeToMove = 0;
	float timeProgressed = 0;
	bool moving = false;
	bool scaling = false;
	bool rotating = false;
};

