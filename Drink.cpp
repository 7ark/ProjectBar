#include "Drink.h"

Drink::Drink()
{
	liquidIncrements = 1.0f / maxAmount;
}

float Drink::FillAmount()
{
	return liquids.size() * liquidIncrements;
}

bool Drink::HasLiquid(LiquidTypes type)
{
	for (int i = 0; i < liquids.size(); i++)
	{
		if (std::find(liquids.begin(), liquids.end(), type) != liquids.end())
		{
			return true;
		}
	}
	return false;
}

bool Drink::AddDrink(LiquidTypes type)
{
	if (IsFull())
	{
		return false;
	}
	else
	{
		liquids.push_back(type);
		lastLiquid = type;
		return true;
	}
}
