#pragma once
#include "Common.h"
#include "Component.h"
#include "Race.h"
#include "Drink.h"
#include "Dialogue.h"

enum class Gender { Male, Female, Other };

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

	CustomerReaction EvaluateDrink(Drink drink);

private:
	CustomerReaction currentState = CustomerReaction::Neutral;
};

