#include "Move.h"



Move::Move()
{
}


Move::~Move()
{
}

void Move::LerpTo(sf::Vector2f position, float time)
{
	originalPosition = gameObject->GetPosition();
	targetPosition = position;
	timeToMove = time;
	timeProgressed = 0;
	moving = true;
}
void Move::LerpTo(sf::Vector2f position, sf::Vector2f scale, float time)
{
	originalPosition = gameObject->GetPosition();
	targetPosition = position;
	originalScale = gameObject->GetScale();
	targetScale = scale;
	timeToMove = time;
	timeProgressed = 0;
	moving = true;
	scaling = true;
}

void Move::Update(float deltaTime)
{
	if (moving)
	{
		timeProgressed += deltaTime;
		if (timeProgressed > timeToMove) timeProgressed = timeToMove;
		float val = (timeProgressed / timeToMove);
		gameObject->SetPosition(Lerp(originalPosition, targetPosition, val));
		if (scaling)
			gameObject->SetScale(Lerp(originalScale, targetScale, val));

		if (val >= 1)
		{
			moving = false;
			scaling = false;
		}
	}
}
