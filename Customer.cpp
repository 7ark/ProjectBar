#include "Customer.h"



Customer::Customer()
{
	customerDialogue.SetDialogue();
}


Customer::~Customer()
{
}

void Customer::Update(float deltaTime)
{
}

CustomerReaction Customer::EvaluateDrink(Drink drink)
{
	for (int i = 0; i < race.poisonous.size(); i++)
	{
		if (drink.HasLiquid(race.poisonous[i]))
		{
			return CustomerReaction::Dead;
		}
	}

	for (int i = 0; i < preferredLiquids.size(); i++)
	{
		if (drink.HasLiquid(preferredLiquids[i]))
		{
			return CustomerReaction::Liked;
		}
	}

	for (int i = 0; i < dislikedLiquids.size(); i++)
	{
		if (drink.HasLiquid(dislikedLiquids[i]))
		{
			return CustomerReaction::Disliked;
		}
	}

	return CustomerReaction::Neutral;
}
