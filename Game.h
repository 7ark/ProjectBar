#pragma once
#include "Common.h"
#include "ResourceManager.h"
#include "Race.h"
#include "Component.h"

class GameObject;
class Animation;

enum class GameState { PreOpen, Open, WithCustomer, Billing };

class Game
{
public:
	static ResourceManager resourceManager;
	static bool menuOpen;
	static GameState currentGameState;

	Game();
	~Game();

	void Run(sf::RenderWindow& window, sf::View& view, sf::View& viewUI);
	void CheckEvents(sf::RenderWindow& window);

	void Update(float deltaTime);

	void Draw(sf::RenderTarget& target, sf::View& view, sf::View& viewUI);

	static sf::RenderWindow* window;

private:

	void Setup(Scenes scene);

	void Open();
	void ServeDrink();

	void CustomerEnter();



	const sf::Vector2f doorPosition = sf::Vector2f(300, 300);

	std::vector<GameObject*> customersInBar;
	GameObject* currentCustomer;

	//Objects
	GameObject* counter;
	GameObject* bartender;
	GameObject* sign;
	Animation* signOpen;
	Animation* signClosed;
};

