#pragma once
#include "Common.h"
#include "ResourceManager.h"
#include "Race.h"
#include "Customer.h"
#include "Component.h"
#include "Drink.h"
#include "Text.h"

class GameObject;
class Animation;
class Button;

enum class GameState { PreOpen, Open, WithCustomer, CustomerTalking, Billing };

class Game
{
public:
	static ResourceManager resourceManager;
	static bool menuOpen;
	static GameState currentGameState;

	Game();
	~Game();

	void Run(sf::RenderWindow& window, sf::View& view, sf::View& viewUI, sf::View& viewBev);
	void CheckEvents(sf::RenderWindow& window);

	void Update(float deltaTime);

	void Draw(sf::RenderTarget& target, sf::View& view, sf::View& viewUI, sf::View& viewBev);
	void Pour();

	static sf::RenderWindow* window;

private:

	void Setup(Scenes scene);

	void Open();
	void ServeDrink();
	void EvaluateCustomerReaction(CustomerState reaction);
	void SetNewGlass();
	void CreateLiquidAsset();
	void EmptyDrink();

	void DefineNewCharacter(Customer* customer);
	void CustomerEnter();

	void DestroyCurrentGlass();
	void DestroyCurrentLiquid();


	const sf::Vector2f doorPosition = sf::Vector2f(300, 300);

	//Drinks and customers and shit
	LiquidTypes selectedTapper = LiquidTypes::Water;
	std::vector<GameObject*> customersInBar; //Customers that have come in, and are in the background drinking.
	Customer* currentCustomer;
	Drink currentDrink;
	std::vector<std::string> currentDialogueTree;
	std::map<DialogueOptions, Button*> dialogueButtons;
	int dialogueTreeIndex = 0;
	bool drinkHasBeenServed = false;

	//Objects
	GameObject* counter;
	GameObject* bartender;
	GameObject* sign;
	GameObject* currentGlass;
	GameObject* currentLiquid;
	GameObject* liquidStream; 
	GameObject* dialogueBox;
	Text* currentDisplayedDialogue;
	Animation* liquidStreamAnim;
	Animation* signOpen;
	Animation* signClosed;
};

