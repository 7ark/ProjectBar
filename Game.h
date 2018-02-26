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

private:

	void Setup();

	GameObject* bartender;

};

