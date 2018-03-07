#pragma once
#include "Common.h"
#include "Component.h"
#include "Race.h"

class Customer : public Component
{
public:
	Customer();
	~Customer();

	Race race;
	std::vector<Drinks> preferredDrinks;
	
};

