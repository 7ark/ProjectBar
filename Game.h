#pragma once
#include "Common.h"
#include "ResourceManager.h"

class GameObject;

class Game
{
public:
	static ResourceManager resourceManager;

	Game();
	~Game();

	void Update(float deltaTime);

	void Draw(sf::RenderTarget& target);

private:

	void Setup();

};

