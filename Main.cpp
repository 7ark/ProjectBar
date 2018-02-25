#include "Common.h"
#include "Object.h"
#include "Game.h"
#include "ObjectManager.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "The Bar");
	sf::View mainView;
	mainView.setSize(sf::Vector2f(1280, 720));
	mainView.setCenter(sf::Vector2f(0, 0));

	Game mainGame;
	sf::Clock clock;

	while (window.isOpen())
	{
		mainGame.Update(clock.restart().asSeconds());

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}
		}
		window.clear();
		window.setView(mainView);
		mainGame.Draw(window);
		window.display();
	}

	return 0;
}