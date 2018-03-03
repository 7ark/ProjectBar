#include "Game.h"
#include "ObjectManager.h"
#include "GameObject.h"
#include "Text.h"
#include "Animation.h"
#include "DisplayObject.h"

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

	GameObject* journal = ObjectManager::CreateObject("Journal", Textures::Journal, sf::Vector2f(150, -300));
	journal->SetScale(sf::Vector2f(0.2f, 0.2f));
	char* journalNotes[4] = 
	{
		"Humans: Weak creatures that love\nto kill shit\n\nDrinks They Enjoy: Any kind of beer\n\nPoisonous: Acid",
		"Animals: I don't know, I'm just\ntrying to fill up some of the space in this book.\n\nDrinks They Enjoy: Water???\n\nPoisonous: Literally everything",
		"Something else: I'm just trying to fill\npages at this point to be honest.\n\nDrinks They Enjoy: Who?? \nThis isn't very specific\n\nPoisonous: Memes",
		"Manpat: Best god damn #other-dev dude.\n\nDrinks They Enjoy: sarsaparilla and \norange juice\n\nPoisonous: Everything humans die from"
	};
	journal->AddComponent<DisplayObject>(Comp::DisplayObject)->Init(Textures::JournalOpen, 4, journalNotes, Textures::Journal, Textures::JournalHighlight);

	GameObject* newspaper = ObjectManager::CreateObject("Newspaper", Textures::Newspaper, sf::Vector2f(-150, -300));
	newspaper->SetScale(sf::Vector2f(0.2f, 0.2f));
	char* newsNotes[4] =
	{
		"BREAKING NEWS\n\nPrime Minister Bob shot by unknown\nassailant, status is unknown at this time.\n\n\nMan Found Drinking Water\n\nLate tuesday evening a man was found\ndrinking water. Find out how he almost\ndied tonight, at 11pm.\n\n\nCat Stuck in Tree\n\nThere's a cat stuck in a tree. He's still\nthere. Can someone please help us?",
		"Batman Lost a Foot\n\nWe've searched literally all over Gotham\nbut we cannot find it. Keep an\neye out.\n\n\nDance Party\n\nThere will be a dance party for the town!\nFeel free to come and enjoy. Except you,\nJessica.\n\n\nGDL Voted Best Server\n\nThe Discord GDL was voted best server by\npretty much everyone.",
		"Bob's Nats Be Gone\n\nCan someone help Bob? He's gone\nand lost his nats again.\n\n\nWoman Found Not Drinking Water\n\nEarly tuesday morning a woman was found\nwithout being able to drink water.\nFind out how she almost lived today, at 1am.\n\n\nCat Stuck in Me\n\nOh god someone please help!",
		"New Show\n\nThere's a new show in town, but nobody\nknows what it is. 0/10\n\n\nInternet Cancelled\n\nIt was decided by the internet gods\nthat on 3/4/18 the internet would be\ncancelled.\n\n\nIdk Man I Just Work Here\n\nWell I gotta type something for an article?\nHell if I know what to type."
	};
	newspaper->AddComponent<DisplayObject>(Comp::DisplayObject)->Init(Textures::JournalOpen, 4, newsNotes, Textures::Newspaper, Textures::NewspaperHighlight);
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
