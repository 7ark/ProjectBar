#include "Button.h"
#include "GameObject.h"
#include "Game.h"

void Button::Update(float deltaTime)
{
	if (!enabled) 
		return;
	sf::Vector2f pos = Game::window->mapPixelToCoords(sf::Mouse::getPosition(*Game::window));
	if (gameObject->GetSprite().getGlobalBounds().contains(pos))
	{
		if (!inBox)
		{
			if(pointerEnter.size() > 0)
				CallDelegate(pointerEnter);
			PointerEnter();
		}
		inBox = true;
	}
	else
	{
		if (inBox)
		{
			if(pointerExit.size() > 0)
				CallDelegate(pointerExit);
			PointerExit();
		}
		inBox = false;
	}
	if (inBox)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouseDown)
			canClick = true;
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouseDown && canClick)
		{
			CallDelegate(click);
			Clicked();
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		mouseDown = true;
	else 
	{
		mouseDown = false;
		canClick = false;
	}
	
}

void Button::CallDelegate(std::vector<std::function<void()>> const& del)
{
	for (auto&& call : del)
	{
		call();
	}
}
