#include "Button.h"
#include "GameObject.h"
#include "Game.h"

void Button::Update(float deltaTime)
{
	sf::Vector2f pos = Game::window->mapPixelToCoords(sf::Mouse::getPosition(*Game::window));
	if (gameObject->GetSprite().getGlobalBounds().contains(pos))
	{
		if (!inBox && pointerEnter.size() > 0)
		{
			CallDelegate(pointerEnter);
		}
		inBox = true;
	}
	else
	{
		if (inBox && pointerExit.size() > 0)
		{
			CallDelegate(pointerExit);
		}
		inBox = false;
	}
	if (inBox)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouseDown)
		{
			CallDelegate(click);
			Clicked();
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		mouseDown = true;
	else
		mouseDown = false;
	
}

void Button::CallDelegate(std::vector<std::function<void()>> const& del)
{
	for (auto&& call : del)
	{
		call();
	}
}
