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
	player = ObjectManager::CreateObject("Player", TextureName::Example);
	Animation* ani = player->AddComponent<Animation>();
	Key keys[6]
	{
		Key(0.25f, TextureName::run1),
		Key(0.5f, TextureName::run2),
		Key(0.75f, TextureName::run3),
		Key(1, TextureName::run4),
		Key(1.25f, TextureName::run5),
		Key(1.5f, TextureName::run6),
	};
	ani->SetKeys(keys, 6);
	ani->Play();
}

void Game::Run(sf::RenderWindow& window,sf::View& view)
{
	sf::Clock clock;

	//Game loop
	while (window.isOpen())
	{
		CheckEvents(window);
		Update(clock.getElapsedTime().asSeconds());

		window.clear();
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
