#include "Text.h"
#include "Game.h"


Text::Text(std::string _name, Fonts const & fontName, sf::String txt, sf::Vector2f position)
{
	name = _name;
	sf::Font* font = Game::resourceManager.RetrieveFont(fontName);
	SetFont(*font);
	SetText(txt);
	SetPosition(position);
}

Text::~Text()
{
}
