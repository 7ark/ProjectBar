#pragma once

struct HelperFunctions
{
	static sf::Vector2f Lerp(sf::Vector2f one, sf::Vector2f two, float delta)
	{
		return one + delta * (two - one);
	}

	template<class T>
	static typename T::iterator remove(typename T::iterator begin, typename T::iterator end, typename T::value const& value) {
		return std::remove_if(begin, end, [&value](T::value const& other) {
			return value == other;
		});
	}
};