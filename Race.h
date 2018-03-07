#pragma once
#include "Common.h"

struct Race
{
	Race();
	~Race();

	sf::String name;
	std::vector<Drinks> poisonous;
};

struct Human : Race
{
	Human()
	{
		name = "Human";
		poisonous.push_back(Drinks::Cyanide);
		poisonous.push_back(Drinks::Arsenic);
	}
};