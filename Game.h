#pragma once
#include "Common.h"
#include "ResourceManager.h"

#include "Component.h"

class GameObject;

class Game
{
public:
	static ResourceManager resourceManager;

	Game();
	~Game();

	void Run(sf::RenderWindow& window, sf::View& view);
	void CheckEvents(sf::RenderWindow& window);

	void Update(float deltaTime);

	void Draw(sf::RenderTarget& target);

	static sf::Vector2f MousePosition();

	static sf::RenderWindow* window;

	static sf::View* worldView;

private:

	static sf::Vector2f mousePos;

	void Setup();

	GameObject* bartender;

};

