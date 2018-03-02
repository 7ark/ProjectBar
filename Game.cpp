#include "Game.h"
#include "ObjectManager.h"
#include "GameObject.h"
#include "Text.h"
#include "Animation.h"
#include "JournalDisplay.h"

ResourceManager Game::resourceManager;

sf::Vector2f Game::mousePos;
sf::RenderWindow* Game::window;
sf::View* Game::worldView;

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
	GameObject* background = ObjectManager::CreateObject("BarBackground", Textures::BarBackground);
	background->SetLayer(-1);
	background->Scale(sf::Vector2f(2, 2));

	GameObject* counter = ObjectManager::CreateObject("Counter", Textures::BarCounter, sf::Vector2f(100, -300));

	bartender = ObjectManager::CreateObject("Bartender", Textures::Bartender, sf::Vector2f(300,-250));
	bartender->SetLayer(2);

	GameObject* journal = ObjectManager::CreateObject("Journal", Textures::Journal, sf::Vector2f(0, -300));
	journal->SetScale(sf::Vector2f(0.2f, 0.2f));
	journal->AddComponent<JournalDisplay>(Comp::JournalDisplay);
}

void Game::Run(sf::RenderWindow& window,sf::View& view)
{
	Game::window = &window;
	Game::worldView = &view;
	sf::Clock clock;

	//Game loop
	while (window.isOpen())
	{
		sf::Vector2i m = sf::Mouse::getPosition(window);
		mousePos = sf::Vector2f(m.x, m.y);

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

sf::Vector2f Game::MousePosition()
{
	return mousePos;
}
