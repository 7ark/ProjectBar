#pragma once
#include "Common.h"
#include "Drink.h"

enum class Races { Human };

struct Race
{
	Race();
	~Race();

	sf::String name;
	std::vector<LiquidTypes> poisonous;
};

struct Human : Race
{
	Human()
	{
		name = "Human";
		poisonous.push_back(LiquidTypes::Cyanide);
		poisonous.push_back(LiquidTypes::Arsenic);
	}
};