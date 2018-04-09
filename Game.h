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

enum class GameState { PreOpen, Open, WithCustomer, CustomerThinking, CustomerTalking, Billing };
enum class TalkingMode { None, Questions, Reaction };

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
	void EvaluateCustomerReaction(CustomerReaction reaction);
	void SetNewGlass();
	void CreateLiquidAsset();
	void EmptyDrink();
	void SendCustomerToTable();

	void DefineNewCharacter(Customer* customer);
	void CustomerEnter();

	void DestroyCurrentGlass();
	void DestroyCurrentLiquid();


	const sf::Vector2f doorPosition = sf::Vector2f(700, 400);
	const int maxQuestionCount = 2;


	//Drinks and customers and shit
	TalkingMode talkingMode = TalkingMode::None;
	CustomerReaction currentReaction;

	LiquidTypes selectedTapper = LiquidTypes::Water;
	Customer* currentCustomer;
	Drink currentDrink;
	std::vector<std::string> currentDialogueTree;
	std::map<DialogueOptions, Button*> dialogueButtons;
	int lastTableLeft = 0;
	int dialogueTreeIndex = 0;
	int questionsAllowed = 0;
	bool drinkHasBeenServed = false;

	//Objects
	GameObject* counter;
	GameObject* bartender;
	GameObject* sign;
	GameObject* currentGlass;
	GameObject* currentLiquid;
	GameObject* liquidStream; 
	GameObject* dialogueBox;
	std::vector<GameObject*> tables;
	std::vector<GameObject*> customersInBar; //Customers that have come in, and are in the background drinking.
	Text* currentDisplayedDialogue;
	Animation* liquidStreamAnim;
	Animation* signOpen;
	Animation* signClosed;
};

