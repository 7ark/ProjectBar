#include "Game.h"
#include "ObjectManager.h"
#include "GameObject.h"
#include "Text.h"
#include "DisplayObject.h"
#include "Animation.h"
#include "Customer.h"
#include "Move.h"

ResourceManager Game::resourceManager;
bool Game::menuOpen = false;

sf::RenderWindow* Game::window;
GameState Game::currentGameState = GameState::PreOpen;

Game::Game()
{
	resourceManager.Init();
	for (size_t i = 0; i < (int)Scenes::Length; i++)
	{
		Setup((Scenes)i);
	}
}

Game::~Game()
{
	resourceManager.Destroy();
}

void Game::Setup(Scenes scene)
{
	//I don't know if there's a better way to create all of these initial objects? So this is just how I'ma do it.
	switch (scene)
	{
	case Scenes::SceneAll: 
	{
		GameObject* background = ObjectManager::CreateObject("BarBackgroundLeft", scene, Textures::BarBackground);
		background->SetLayer(-20);
		background->Scale(sf::Vector2f(4, 4));

		counter = ObjectManager::CreateObject("CounterLeft", scene, Textures::BarCounter, sf::Vector2f(100, -400));
		counter->SetLayer(5);
		counter->SetScale(sf::Vector2f(1.0f, 1.0f));
	}
		break;
	case Scenes::SceneLeft:
	{

	}
	break;
	case Scenes::SceneRight:
	{
		bartender = ObjectManager::CreateObject("Bartender", scene, Textures::Bartender, sf::Vector2f(100, -350));
		bartender->SetScale(sf::Vector2f(1.5f, 1.5f));
		bartender->SetLayer(10);
	}
	break;
	case Scenes::UI:
	{
		GameObject* journal = ObjectManager::CreateObject("Journal", scene, Textures::Journal, sf::Vector2f(-500, -300));
		journal->SetScale(sf::Vector2f(0.2f, 0.2f));
		char* journalNotes[4] =
		{
			"Humans: Weak creatures that love\nto kill shit\n\nDrinks They Enjoy: Any kind of beer\n\nPoisonous: Acid",
			"Animals: I don't know, I'm just\ntrying to fill up some of the space in this book.\n\nDrinks They Enjoy: Water???\n\nPoisonous: Literally everything",
			"Something else: I'm just trying to fill\npages at this point to be honest.\n\nDrinks They Enjoy: Who?? \nThis isn't very specific\n\nPoisonous: Memes",
			"Manpat: Best god damn #other-dev dude.\n\nDrinks They Enjoy: sarsaparilla and \norange juice\n\nPoisonous: Everything humans die from"
		};
		journal->AddComponent<DisplayObject>(Comp::DisplayObject)->Init(Textures::JournalOpen, 4, journalNotes, Textures::Journal, Textures::JournalHighlight);

		GameObject* newspaper = ObjectManager::CreateObject("Newspaper", scene, Textures::Newspaper, sf::Vector2f(-300, -300));
		newspaper->SetScale(sf::Vector2f(0.2f, 0.2f));
		char* newsNotes[4] =
		{
			"BREAKING NEWS\n\nPrime Minister Bob shot by unknown\nassailant, status is unknown at this time.\n\n\nMan Found Drinking Water\n\nLate tuesday evening a man was found\ndrinking water. Find out how he almost\ndied tonight, at 11pm.\n\n\nCat Stuck in Tree\n\nThere's a cat stuck in a tree. He's still\nthere. Can someone please help us?",
			"Batman Lost a Foot\n\nWe've searched literally all over Gotham\nbut we cannot find it. Keep an\neye out.\n\n\nDance Party\n\nThere will be a dance party for the town!\nFeel free to come and enjoy. Except you,\nJessica.\n\n\nGDL Voted Best Server\n\nThe Discord GDL was voted best server by\npretty much everyone.",
			"Bob's Nats Be Gone\n\nCan someone help Bob? He's gone\nand lost his nats again.\n\n\nWoman Found Not Drinking Water\n\nEarly tuesday morning a woman was found\nwithout being able to drink water.\nFind out how she almost lived today, at 1am.\n\n\nCat Stuck in Me\n\nOh god someone please help!",
			"New Show\n\nThere's a new show in town, but nobody\nknows what it is. 0/10\n\n\nInternet Cancelled\n\nIt was decided by the internet gods\nthat on 3/4/18 the internet would be\ncancelled.\n\n\nIdk Man I Just Work Here\n\nWell I gotta type something for an article?\nHell if I know what to type."
		};
		newspaper->AddComponent<DisplayObject>(Comp::DisplayObject)->Init(Textures::JournalOpen, 4, newsNotes, Textures::Newspaper, Textures::NewspaperHighlight);

		sign = ObjectManager::CreateObject("OpenSign", scene, Textures::SignClosed, sf::Vector2f(450, 330));
		sign->SetScale(sf::Vector2f(0.3f, 0.3f));
		sign->AddComponent<Button>(Comp::Button)->click.push_back(std::bind(&Game::Open, this));

		signOpen = sign->AddComponent<Animation>(Comp::Animation);
		Key openKeys[2] =
		{
			Key(0,Textures::SignClosed),
			Key(0,Textures::SignOpen)
		};
		signOpen->SetKeys(openKeys, 2);

		signClosed = sign->AddComponent<Animation>(Comp::Animation);
		Key closedKeys[2] =
		{
			Key(0,Textures::SignOpen),
			Key(0,Textures::SignClosed)
		};
		signClosed->SetKeys(closedKeys, 2);
	}
		break;
	}
	
}

void Game::Open()
{
	if (currentGameState == GameState::PreOpen) 
	{
		signOpen->Play();
		currentGameState = GameState::Open;
	}
}

void Game::CustomerEnter()
{
	GameObject* newCustomer = ObjectManager::CreateObject("Customer", Scenes::SceneAll, Textures::Man, doorPosition);
	newCustomer->name = "Customer #"+newCustomer->GetUniqueID(); //We'll give them proper names... once they've earned them!
	newCustomer->SetScale(sf::Vector2f(0.2f, 0.2f));
	newCustomer->AddComponent<Move>(Comp::Move)->LerpTo(counter->GetPosition()+sf::Vector2f(0,150), sf::Vector2f(0.3f, 0.3f), 3);
}

void Game::Run(sf::RenderWindow& window,sf::View& view, sf::View& viewUI)
{
	Game::window = &window;
	sf::Clock clock; 
	srand(time(NULL));

	float newCustomerFrequency = rand()%3+2;
	float customerTimer = 0;

	//Game loop
	while (window.isOpen())
	{
		//Input and shit
		CheckEvents(window);

		//Update Objects
		float deltaTime = clock.restart().asSeconds();
		Update(deltaTime);

		//Game Update
		switch (currentGameState)
		{
		case GameState::PreOpen:
			break;
		case GameState::Open:
			if (!withCustomer)
			{
				customerTimer += deltaTime;
				if (customerTimer >= newCustomerFrequency)
				{
					CustomerEnter();
					withCustomer = true;
				}
			}
			break;
		case GameState::Billing:
			break;
		default:
			break;
		}

		//Draw all of our everything
		Draw(window, view, viewUI);
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

void Game::Draw(sf::RenderTarget & target, sf::View& view, sf::View& viewUI)
{
	target.clear(sf::Color::Cyan);

	sf::View viewLeft = view;
	viewLeft.setCenter(sf::Vector2f(100, 200));
	viewLeft.setViewport(sf::FloatRect(0, 0, 0.5f, 1));
	viewLeft.zoom(0.8f);

	sf::View viewRight = view;
	viewRight.setViewport(sf::FloatRect(0.5f, 0, 0.5f, 1));
	viewRight.zoom(1.4f);

	target.setView(viewLeft);
	ObjectManager::DrawObjects(target, Scenes::SceneLeft);

	target.setView(viewRight);
	ObjectManager::DrawObjects(target, Scenes::SceneRight);

	target.setView(viewUI);
	ObjectManager::DrawObjects(target, Scenes::UI);
}
