#include "Common.h"
#include "Object.h"
#include "Game.h"
#include "ObjectManager.h"

int main()
{
	GameSettings::width = 1280;
	GameSettings::height = 720;
	sf::RenderWindow window(sf::VideoMode(GameSettings::width, GameSettings::height), "The Bar");

	sf::View mainView;
	mainView.setSize(sf::Vector2f(GameSettings::width, GameSettings::height));
	mainView.setCenter(sf::Vector2f(0, 0));

	Game mainGame;
	mainGame.Run(window, mainView);

	return 0;
}