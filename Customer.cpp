#include "Customer.h"



Customer::Customer()
{
}


Customer::~Customer()
{
}

void Customer::Update(float deltaTime)
{
}

CustomerState Customer::EvaluateDrink(Drink drink)
{
	for (int i = 0; i < race.poisonous.size(); i++)
	{
		if (drink.HasLiquid(race.poisonous[i]))
		{
			return CustomerState::Dead;
		}
	}

	for (int i = 0; i < preferredLiquids.size(); i++)
	{
		if (drink.HasLiquid(preferredLiquids[i]))
		{
			return CustomerState::Liked;
		}
	}

	for (int i = 0; i < dislikedLiquids.size(); i++)
	{
		if (drink.HasLiquid(dislikedLiquids[i]))
		{
			return CustomerState::Disliked;
		}
	}

	return CustomerState::Neutral;
}
