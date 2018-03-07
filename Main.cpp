#include "Common.h"
#include "Object.h"
#include "Game.h"
#include "ObjectManager.h"
#include <Windows.h>

int main()
{
	if(!GameSettings::DEBUG)
		FreeConsole();
	GameSettings::width = 1280;
	GameSettings::height = 720;
	GameSettings::halfWidth = GameSettings::width * 0.5f;
	GameSettings::halfHeight = GameSettings::height * 0.5f;
	sf::RenderWindow window(sf::VideoMode(GameSettings::width, GameSettings::height), "The Bar");

	sf::View sceneView;
	sceneView.setSize(sf::Vector2f(GameSettings::halfWidth, GameSettings::height));
	sceneView.setCenter(sf::Vector2f(0, 0));
	sceneView.setViewport(sf::FloatRect(0, 0, 0.5f, 1));

	sf::View UIView;
	UIView.setSize(sf::Vector2f(GameSettings::width, GameSettings::height));
	UIView.setCenter(sf::Vector2f(0, 0));

	Game mainGame;
	mainGame.Run(window, sceneView, UIView);

	return 0;
}