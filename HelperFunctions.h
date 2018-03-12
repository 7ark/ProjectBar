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

	static float Clamp(float value, float min, float max)
	{
		return value > max ? max : value < min ? min : value;
	}
	
	static float Clamp01(float value)
	{
		return Clamp(value, 0, 1);
	}

	template<class T>
	static typename T::iterator remove(typename T::iterator begin, typename T::iterator end, typename T::value const& value) {
		return std::remove_if(begin, end, [&value](T::value const& other) {
			return value == other;
		});
	}
};