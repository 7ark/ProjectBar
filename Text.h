#pragma once
#include "Object.h"

class Game;

class Text : public Object
{
public:
	Text(std::string _name, Fonts const & textureName, sf::String txt = "", sf::Vector2f position = sf::Vector2f(0, 0));
	~Text();

	//Setters
	void SetText(sf::String txt) { text.setString(txt); }
	void SetFont(sf::Font& font) { text.setFont(font); }
	void SetColor(sf::Color col) { text.setFillColor(col); }

	//Getters
	sf::String GetText() { return text.getString(); }
	sf::Font GetFont() { return *text.getFont(); }
	sf::Color GetColor() { return text.getFillColor(); }

protected:
	sf::Text text;

	virtual void onDraw(sf::RenderTarget& target, sf::Transformable& transform)
	{
		text.setPosition(transform.getPosition());
		text.setScale(transform.getScale());
		text.setRotation(transform.getRotation());
		if (enabled && visible)
			target.draw(text);
	}
};

