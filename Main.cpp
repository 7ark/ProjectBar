#include "Common.h"
#include "Object.h"
#include "Game.h"
#include "ObjectManager.h"
#include <Windows.h>

int main()
{
#ifdef _DEBUG
	GameSettings::DEBUG = true;
#else
	GameSettings::DEBUG = false;
#endif

	if(!GameSettings::DEBUG)
		FreeConsole();
	GameSettings::windowWidth = 1280;
	GameSettings::windowHeight = 720;
	GameSettings::resolutionWidth = 1920;
	GameSettings::resolutionHeight = 1080;
	GameSettings::uiReferenceWidth = 1920;
	GameSettings::uiReferenceHeight = 1080;

	GameSettings::resolutionWidthHalf = GameSettings::resolutionWidth * 0.5f;
	GameSettings::resolutionHeightHalf = GameSettings::resolutionHeight * 0.5f;
	GameSettings::uiReferenceWidthHalf = GameSettings::uiReferenceWidth * 0.5f;
	GameSettings::uiReferenceHeightHalf = GameSettings::uiReferenceHeight * 0.5f;

	sf::RenderWindow window(sf::VideoMode(GameSettings::windowWidth, GameSettings::windowHeight), "The Bar");

	sf::View sceneView;
	sceneView.setSize(sf::Vector2f(GameSettings::resolutionWidthHalf, GameSettings::resolutionHeight));
	sceneView.setCenter(sf::Vector2f(0, 0));
	sceneView.setViewport(sf::FloatRect(0, 0, 0.5f, 1));

	sf::View UIView;
	UIView.setSize(sf::Vector2f(GameSettings::resolutionWidth, GameSettings::resolutionHeight));
	UIView.setCenter(sf::Vector2f(0, 0));

	sf::View beverageView;
	beverageView.setSize(sf::Vector2f(GameSettings::resolutionWidth/6, GameSettings::resolutionHeight));
	beverageView.setCenter(sf::Vector2f(0, 0));

	Game mainGame;
	mainGame.Run(window, sceneView, UIView, beverageView);

	return 0;
}