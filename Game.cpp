#include "Game.h"
#include "ObjectManager.h"
#include "GameObject.h"
#include "Animation.h"

ResourceManager Game::resourceManager;

Game::Game()
{
	resourceManager.Init();
	Setup();
}

Game::~Game()
{
	resourceManager.Destroy();
}

void Game::Setup()
{
	GameObject* background = ObjectManager::CreateObject("BarBackground", TextureName::BarBackground);
	background->SetLayer(-1);
	background->transform.scale(sf::Vector2f(2, 2));
	GameObject* counter = ObjectManager::CreateObject("Counter", TextureName::BarCounter, sf::Vector2f(100, -400));
	bartender = ObjectManager::CreateObject("Bartender", TextureName::Bartender, sf::Vector2f(300,-250));
	bartender->SetLayer(2);
}

void Game::Run(sf::RenderWindow& window,sf::View& view)
{
	sf::Clock clock;

	//Game loop
	while (window.isOpen())
	{
		CheckEvents(window);
		Update(clock.getElapsedTime().asSeconds());

		window.clear(sf::Color::White);
		window.setView(view);
		Draw(window);
		window.display();
	}
}

void Game::CheckEvents(sf::RenderWindow& window)
{
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
}


void Game::Update(float deltaTime)
{
	ObjectManager::UpdateObjects(deltaTime);
}

void Game::Draw(sf::RenderTarget & target)
{
	ObjectManager::DrawObjects(target);
}
