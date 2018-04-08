#pragma once
#include "Common.h"

#pragma region Liquid

enum class LiquidTypes
{
	Water,
	Beer,
	Arsenic,
	Cyanide,

	Length
};

class LiquidUtils
{
public:
	static sf::Color GetColor(LiquidTypes type)
	{
		switch (type)
		{
		case LiquidTypes::Water:
			return sf::Color(220, 220, 220, 127);
		case LiquidTypes::Beer:
			return sf::Color::Yellow;
		case LiquidTypes::Arsenic:
			return sf::Color(200, 200, 255);
		case LiquidTypes::Cyanide:
			return sf::Color(255, 255, 255);
		default:
			return sf::Color::Black;
		}
	}

	static char* GetName(LiquidTypes type)
	{
		switch (type)
		{
		case LiquidTypes::Water:
			return "Water";
		case LiquidTypes::Beer:
			return "Beer";
		case LiquidTypes::Arsenic:
			return "Arsenic";
		case LiquidTypes::Cyanide:
			return "Cyanide";
		default:
			return "Invalid";
		}
	}
};

#pragma endregion

class Drink
{
public:
	Drink();

	const int maxAmount = 4;

	bool IsFull() { return liquids.size() >= maxAmount; }

	float FillAmount();

	int TimesPoured() { return liquids.size(); }

	LiquidTypes GetLiquidAtIndex(int i) { return liquids[i]; }

	LiquidTypes LastLiquidAdded() { return lastLiquid; }

	float LiquidIncrements() { return liquidIncrements; }

	void Empty() { liquids.clear(); }

	bool HasLiquid(LiquidTypes type);

	bool AddDrink(LiquidTypes type);

private:
	std::vector<LiquidTypes> liquids;
	LiquidTypes lastLiquid;

	float liquidIncrements = 0;
};

