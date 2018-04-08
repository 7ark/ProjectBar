#pragma once
#include "Common.h"
#include "Component.h"
#include "Race.h"
#include "Drink.h"
#include "Dialogue.h"

enum class Gender { Male, Female, Other };
enum class CustomerState { Null, Liked, Neutral, Disliked, Dead };

class Customer : public Component
{
public:
	Customer();
	~Customer();

	void Update(float deltaTime);

	char* name;
	Race race;
	Gender gender;
	std::vector<LiquidTypes> preferredLiquids;
	std::vector<LiquidTypes> dislikedLiquids;
	Dialogue customerDialogue;

	CustomerState EvaluateDrink(Drink drink);

private:
	CustomerState currentState = CustomerState::Neutral;
};

