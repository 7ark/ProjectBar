#pragma once

struct HelperFunctions
{
	static sf::Vector2f Lerp(sf::Vector2f one, sf::Vector2f two, float delta)
	{
		return one + delta * (two - one);
	}

	static float Lerp(float one, float two, float delta)
	{
		return one + delta * (two - one);
	}
	
	static sf::Color Lerp(sf::Color one, sf::Color two, float delta)
	{
		return sf::Color(
			Lerp(one.r, two.r, delta),
			Lerp(one.g, two.g, delta),
			Lerp(one.b, two.b, delta),
			Lerp(one.a, two.a, delta)
		);
	}

	static float Clamp(float value, float min, float max)
	{
		return value > max ? max : value < min ? min : value;
	}
	
	static float Clamp01(float value)
	{
		return Clamp(value, 0, 1);
	}

	static float Max(float one, float two)
	{
		return one > two ? one : two;
	}

	static float Min(float one, float two)
	{
		return one < two ? one : two;
	}
};