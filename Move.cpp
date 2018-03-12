#include "Move.h"



Move::Move()
{
}


Move::~Move()
{
}

void Move::LerpTo(sf::Vector2f position, float time, std::function<void()> callback)
{
	currentCallback = callback;
	originalPosition = gameObject->GetPosition();
	targetPosition = position;
	timeToMove = time;
	timeProgressed = 0;
	moving = true;
}
void Move::LerpTo(sf::Vector2f position, sf::Vector2f scale, float time, std::function<void()> callback)
{
	currentCallback = callback;
	originalPosition = gameObject->GetPosition();
	targetPosition = position;
	originalScale = gameObject->GetScale();
	targetScale = scale;
	timeToMove = time;
	timeProgressed = 0;
	moving = true;
	scaling = true;
}

void Move::LerpTo(sf::Vector2f position, float rotation, float time, std::function<void()> callback)
{
	currentCallback = callback;
	originalPosition = gameObject->GetPosition();
	targetPosition = position;
	originalRotation = gameObject->GetRotation();
	targetRotation = rotation;
	timeToMove = time;
	timeProgressed = 0;
	moving = true;
	rotating = true;
}

void Move::Update(float deltaTime)
{
	if (moving)
	{
		timeProgressed += deltaTime;
		if (timeProgressed > timeToMove) timeProgressed = timeToMove;
		float val = (timeProgressed / timeToMove);
		gameObject->SetPosition(HelperFunctions::Lerp(originalPosition, targetPosition, val));
		if (scaling)
			gameObject->SetScale(HelperFunctions::Lerp(originalScale, targetScale, val));
		if (rotating)
			gameObject->SetRotation(HelperFunctions::Lerp(originalRotation, targetRotation, val));

		if (val >= 1)
		{
			moving = false;
			scaling = false;
			rotating = false;
			std::function<void()> call = currentCallback;
			currentCallback = nullptr;
			if(call != nullptr)
				call();
		}
	}
}
