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
			background->Scale(sf::Vector2f(4, 4.5f));

			counter = ObjectManager::CreateObject("CounterLeft", scene, Textures::BarCounter, sf::Vector2f(100, -500));
			counter->SetLayer(5);
			counter->SetScale(sf::Vector2f(1.3f, 1.3f));

			GameObject* tapper = ObjectManager::CreateObject("Tapper", scene, Textures::Tapper, sf::Vector2f(500, -150));
			tapper->SetLayer(7);

			liquidStream = ObjectManager::CreateObject("LiquidStream", scene, Textures::WhiteBar, sf::Vector2f(465, -230));
			liquidStream->SetLayer(8);
			liquidStream->SetScale(sf::Vector2f(0.1f,0.5f));
			liquidStream->SetActive(false);
			liquidStreamAnim = liquidStream->AddComponent<Animation>(Comp::Animation);
			//Alright listen. If you're looking at this, this is temporary. I'm too lazy to figure out how to make
			//the proper for loop to make this loop just right. I could be all fancy and use sin and make it look
			//all pretty. But it works, and it's temporary, so who cares? Amiright?
			Key liquidKeys[16] =
			{
				Key(Textures::WhiteBar, sf::Vector2f(1,1)),
				Key(Textures::WhiteBar, sf::Vector2f(1.1f,1)),
				Key(Textures::WhiteBar, sf::Vector2f(1.2f,1)),
				Key(Textures::WhiteBar, sf::Vector2f(1.3f,1)),
				Key(Textures::WhiteBar, sf::Vector2f(1.4f,1)),
				Key(Textures::WhiteBar, sf::Vector2f(1.3f,1)),
				Key(Textures::WhiteBar, sf::Vector2f(1.2f,1)),
				Key(Textures::WhiteBar, sf::Vector2f(1.1f,1)),
				Key(Textures::WhiteBar, sf::Vector2f(1,1)),
				Key(Textures::WhiteBar, sf::Vector2f(0.9f,1)),
				Key(Textures::WhiteBar, sf::Vector2f(0.8f,1)),
				Key(Textures::WhiteBar, sf::Vector2f(0.7f,1)),
				Key(Textures::WhiteBar, sf::Vector2f(0.6f,1)),
				Key(Textures::WhiteBar, sf::Vector2f(0.7f,1)),
				Key(Textures::WhiteBar, sf::Vector2f(0.8f,1)),
				Key(Textures::WhiteBar, sf::Vector2f(0.9f,1))
			};
			liquidStreamAnim->SetKeys(liquidKeys,16);
			liquidStreamAnim->SetConstantTime(0.1f);
			liquidStreamAnim->Play(true);
		}
			break;
		case Scenes::SceneLeft:
		{

		}
		break;
		case Scenes::SceneRight:
		{
			bartender = ObjectManager::CreateObject("Bartender", scene, Textures::Bartender, sf::Vector2f(100, -450));
			bartender->SetScale(sf::Vector2f(2.0f, 2.0f));
			bartender->SetLayer(10);
		}
		break;
		case Scenes::UI:
		{
			#pragma region UI
			//Right now the text for the journal and newspaper is text, but it'll probably be replaced by images later so it can have images and be more detailed.
			GameObject* journal = ObjectManager::CreateObject("Journal", scene, Textures::Journal, sf::Vector2f(-850, -400));
			journal->SetScale(sf::Vector2f(0.3f, 0.3f));
			char* journalNotes[4] =
			{
				"Humans: Weak creatures that love\nto kill shit\n\nDrinks They Enjoy: Any kind of beer\n\nPoisonous: Acid\n\n\n\n\n\n\n\n\n\n\n\n",
				"Animals: I don't know, I'm just\ntrying to fill up some of the space in this book.\n\nDrinks They Enjoy: Water???\n\nPoisonous: Literally everything\n\n\n\n\n\n\n\n\n\n\n\n",
				"Something else: I'm just trying to fill\npages at this point to be honest.\n\nDrinks They Enjoy: Who?? \nThis isn't very specific\n\nPoisonous: Memes\n\n\n\n\n\n\n\n\n\n\n\n",
				"Manpat: Best god damn #other-dev dude.\n\nDrinks They Enjoy: sarsaparilla and \norange juice\n\nPoisonous: Everything humans die from\n\n\n\n\n\n\n\n\n\n\n\n"
			};
			DisplayObject* journalDisplay = journal->AddComponent<DisplayObject>(Comp::DisplayObject);
			journalDisplay->Init(Textures::JournalOpen, 4, journalNotes);
			journalDisplay->SetHighlightShader(resourceManager.RetrieveShader(Shaders::Outline, sf::Shader::Fragment), 10);

			GameObject* newspaper = ObjectManager::CreateObject("Newspaper", scene, Textures::Newspaper, sf::Vector2f(-600, -400));
			newspaper->SetScale(sf::Vector2f(0.3f, 0.3f));
			char* newsNotes[4] =
			{
				"BREAKING NEWS\n\nPrime Minister Bob shot by unknown\nassailant, status is unknown at this time.\n\n\nMan Found Drinking Water\n\nLate tuesday evening a man was found\ndrinking water. Find out how he almost\ndied tonight, at 11pm.\n\n\nCat Stuck in Tree\n\nThere's a cat stuck in a tree. He's still\nthere. Can someone please help us?",
				"Batman Lost a Foot\n\nWe've searched literally all over Gotham\nbut we cannot find it. Keep an\neye out.\n\n\nDance Party\n\nThere will be a dance party for the town!\nFeel free to come and enjoy. Except you,\nJessica.\n\n\nGDL Voted Best Server\n\nThe Discord GDL was voted best server by\npretty much everyone.",
				"Bob's Nats Be Gone\n\nCan someone help Bob? He's gone\nand lost his nats again.\n\n\nWoman Found Not Drinking Water\n\nEarly tuesday morning a woman was found\nwithout being able to drink water.\nFind out how she almost lived today, at 1am.\n\n\nCat Stuck in Me\n\nOh god someone please help!",
				"New Show\n\nThere's a new show in town, but nobody\nknows what it is. 0/10\n\n\nInternet Cancelled\n\nIt was decided by the internet gods\nthat on 3/4/18 the internet would be\ncancelled.\n\n\nIdk Man I Just Work Here\n\nWell I gotta type something for an article?\nHell if I know what to type."
			};
			DisplayObject* newspaperDisplay = newspaper->AddComponent<DisplayObject>(Comp::DisplayObject);
			newspaperDisplay->Init(Textures::JournalOpen, 4, newsNotes);
			newspaperDisplay->SetHighlightShader(resourceManager.RetrieveShader(Shaders::Outline, sf::Shader::Fragment), 10);

			sign = ObjectManager::CreateObject("OpenSign", scene, Textures::SignClosed, sf::Vector2f(650, 500));
			sign->SetScale(sf::Vector2f(0.5f, 0.5f));
			sign->AddComponent<Button>(Comp::Button)->click.push_back(std::bind(&Game::Open, this));

			//In the future hopefully I'll have money to actually get a good sign swinging animation here.
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

			GameObject* serveDrinkButton = ObjectManager::CreateObject("ServeDrinkButton", scene, Textures::SquareButtonUp, sf::Vector2f(-300,-430));
			serveDrinkButton->SetScale(sf::Vector2f(1.5f, 1.5f));
			Button* serveButton = serveDrinkButton->AddComponent<Button>(Comp::Button);
			serveButton->click.push_back([this]() { ServeDrink(); });
			serveButton->SetHighlightShader(resourceManager.RetrieveShader(Shaders::Outline, sf::Shader::Fragment), 1);
			serveButton->SetClickTexture(Textures::SquareButtonUp, Textures::SquareButtonDown);
			Text* serveDrinkText = ObjectManager::CreateText("ServeDrinkButtonText", scene, Fonts::Hughs, "Serve", sf::Vector2f(0, 80));
			serveDrinkText->SetParent(serveDrinkButton);

			GameObject* addGlassButton = ObjectManager::CreateObject("AddGlassButton", scene, Textures::GlassCup, sf::Vector2f(80, -480));
			addGlassButton->SetScale(sf::Vector2f(0.05f, 0.05f));
			addGlassButton->SetRotation(180);
			Button* gButton = addGlassButton->AddComponent<Button>(Comp::Button);
			gButton->click.push_back(std::bind(&Game::SetNewGlass, this));
			gButton->SetHighlightShader(resourceManager.RetrieveShader(Shaders::Outline, sf::Shader::Fragment), 50);

			GameObject* pourButton = ObjectManager::CreateObject("PourButton", scene, Textures::SquareButtonUp, sf::Vector2f(0, 30));
			pourButton->SetScale(sf::Vector2f(3, 1.3f));
			Button* pourButtonComp = pourButton->AddComponent<Button>(Comp::Button);
			pourButtonComp->SetClickTexture(Textures::SquareButtonUp, Textures::SquareButtonDown);
			pourButtonComp->click.push_back([this]() { this->Pour(); });
			Text* pourButtonText = ObjectManager::CreateText("PourButtonText", scene, Fonts::Hughs, "Pour", sf::Vector2f(0, 10));
			pourButtonText->SetParent(pourButton);
			pourButtonText->SetScale(sf::Vector2f(0.5f, 1));

			//Creating the pour buttons
			std::vector<Button*> buttons;
			for (size_t i = 0; i < (int)LiquidTypes::Length; i++)
			{
				char* drinkName = LiquidUtils::GetName((LiquidTypes)i);
				std::string name = std::string(drinkName) + "Button";
				GameObject* drinkTapperButton = ObjectManager::CreateObject(name, scene, Textures::SquareButtonUp, sf::Vector2f(50, 300 - i * 50));
				Button* tapperButton = drinkTapperButton->AddComponent<Button>(Comp::Button);
				buttons.push_back(tapperButton);
				if (LiquidTypes::Water == (LiquidTypes)i) 
					drinkTapperButton->SetSprite(resourceManager.RetrieveTexture(Textures::SquareButtonDown));

				Text* tapperText = ObjectManager::CreateText(name + "Text", scene, Fonts::Hughs, drinkName, sf::Vector2f(-100,5));
				tapperText->SetParent(drinkTapperButton);
			}

			for (size_t i = 0; i < buttons.size(); i++)
			{
				int index = i;
				buttons[i]->click.push_back([this, index, buttons]() 
				{ 
					selectedTapper = (LiquidTypes)index;
					for (size_t j = 0; j < buttons.size(); j++)
					{
						buttons[j]->gameObject->SetSprite(resourceManager.RetrieveTexture(index == j ? Textures::SquareButtonDown : Textures::SquareButtonUp));
					}
				});
			}

			GameObject* frame = ObjectManager::CreateObject("Frame", scene, Textures::Frame, sf::Vector2f(0, 0));
			frame->SetScale(sf::Vector2f(0.2f, 0.52f));
			#pragma endregion
		}
		break;
	}
	
}

void Game::ServeDrink()
{
	if (currentGlass != nullptr && !currentGlass->IsDestroyed())
	{
		CustomerState customerReaction = CustomerState::Null;
		currentGlass->GetComponent<Move>(Comp::Move)->LerpTo(counter->GetPosition() + sf::Vector2f(0, 200), 2, [this, &customerReaction]() 
		{ 
			if(currentCustomer != nullptr) 
				customerReaction = currentCustomer->EvaluateDrink(currentDrink); 
		});
		drinkHasBeenServed = true;

		//Idk do some shit based on what the customer thought.
		//After all, the customer is always right.
		//Unless they died, I guess we won't really care about their opinion then.
		switch (customerReaction)
		{
		case CustomerState::Null:
			break;
		case CustomerState::Liked:
			break;
		case CustomerState::Neutral:
			break;
		case CustomerState::Disliked:
			break;
		case CustomerState::Dead:
			break;
		}
	}
}

void Game::SetNewGlass()
{
	EmptyDrink();
	DestroyCurrentGlass();
	DestroyCurrentLiquid();

	currentGlass = ObjectManager::CreateObject("CurrentGlassCup", Scenes::SceneAll, Textures::GlassCup, sf::Vector2f(570, -500));
	Move* glassMove = currentGlass->AddComponent<Move>(Comp::Move);
	currentGlass->SetLayer(8);
	currentGlass->SetScale(sf::Vector2f(0.05f, 0.05f));
	currentGlass->SetRotation(180);
	glassMove->LerpTo(sf::Vector2f(560, -200), 0, 0.5f, [this]() 
	{ 
		currentGlass->GetComponent<Move>(Comp::Move)->LerpTo(sf::Vector2f(470, -280), 0.3f, std::bind(&Game::CreateLiquidAsset, this)); 
	});
}

void Game::CreateLiquidAsset()
{
	DestroyCurrentLiquid();
	currentLiquid = ObjectManager::CreateObject("Liquid", Scenes::SceneAll, Textures::Liquid);
	currentLiquid->SetLayer(10);
	currentLiquid->SetParent(currentGlass);
	currentLiquid->SetFillMode(FillMode::BottomToTop);
	currentLiquid->SetFillAmount(0);
}

void Game::Pour()
{
	if (drinkHasBeenServed) return;

	LiquidTypes liquid = selectedTapper;
	if (currentLiquid != nullptr && !currentDrink.IsFull())
	{
		currentDrink.AddDrink(liquid);

		std::cout << "Pouring " << LiquidUtils::GetName(liquid) << '\n';
		if (currentDrink.IsFull())
			std::cout << "FULL -------------------------------\n";
	}
}

void Game::EmptyDrink()
{
	currentDrink.Empty();
	liquidStream->SetActive(false);
}

void Game::Open()
{
	if (currentGameState == GameState::PreOpen) 
	{
		signOpen->Play();
		currentGameState = GameState::Open;
	}
}

void Game::DefineNewCharacter(Customer* customer)
{
	//Meet Bob, my temporary whatever character until I figure out how I'm gonna do
	//any kind of random generation or whatever.
	customer->name = "Bob";
	customer->race = Human();
	customer->gender = Gender::Male;
	customer->preferredLiquids.push_back(LiquidTypes::Beer);
	customer->dislikedLiquids.push_back(LiquidTypes::Water);

	customer->gameObject->SetSprite(resourceManager.RetrieveTexture(Textures::Man));
}

void Game::CustomerEnter()
{
	//A customer has appeared
	GameObject* newCustomer = ObjectManager::CreateObject("Customer", Scenes::SceneAll, Textures::Man, doorPosition);
	newCustomer->name = "Customer #"+newCustomer->GetUniqueID(); //We'll give them proper names... once they've earned them!
	newCustomer->SetScale(sf::Vector2f(0.4f, 0.4f));
	newCustomer->AddComponent<Move>(Comp::Move)->LerpTo(counter->GetPosition()+sf::Vector2f(0,150), sf::Vector2f(0.5f, 0.5f), 3);

	Customer* customer = newCustomer->AddComponent<Customer>(Comp::Customer);
	DefineNewCharacter(customer);

	currentCustomer = customer;
}

void Game::DestroyCurrentGlass()
{
	if (currentGlass != nullptr && !currentGlass->IsDestroyed())
	{
		currentGlass->Destroy();
		currentGlass = nullptr;
	}
	drinkHasBeenServed = false;
}

void Game::DestroyCurrentLiquid()
{
	if (currentLiquid != nullptr && !currentLiquid->IsDestroyed())
	{
		currentLiquid->Destroy();
		currentLiquid = nullptr;
	}
}

void Game::Run(sf::RenderWindow& window,sf::View& view, sf::View& viewUI, sf::View& viewBev)
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
			customerTimer += deltaTime;
			if (customerTimer >= newCustomerFrequency)
			{
				CustomerEnter();
				currentGameState = GameState::WithCustomer;
			}
			break;
		case GameState::WithCustomer:
			customerTimer = 0;
			
			break;
		case GameState::Billing:
			break;
		default:
			break;
		}
		//Welcome to The Color Zone
		//Here in the color zone we change the liquids color based on all the liquids in the drink
		if (currentLiquid != nullptr)
		{
			//If the liquids not filled up to the level it should be, let's fill that bad boy up!
			if (currentLiquid->GetFillAmount() < currentDrink.FillAmount())
			{
				//Show the pouring liquid
				liquidStream->SetActive(true);
				liquidStream->SetColor(LiquidUtils::GetColor(currentDrink.LastLiquidAdded()));
				//Increase our fill amount
				currentLiquid->ChangeFillAmount(deltaTime*0.3f);
				//Get the first starting color we need
				sf::Color initialDrinkColor = LiquidUtils::GetColor(currentDrink.GetLiquidAtIndex(0));
				float resultR = initialDrinkColor.r;
				float resultG = initialDrinkColor.g;
				float resultB = initialDrinkColor.b;
				float resultA = initialDrinkColor.a;
				float timesPoured = currentDrink.TimesPoured();
				//Go through all our colors (except the first, duh) and adjust the color for each liquid type
				for (int i = 1; i < timesPoured; i++)
				{
					sf::Color current = LiquidUtils::GetColor(currentDrink.GetLiquidAtIndex(i));

					resultR += current.r;
					resultG += current.g;
					resultB += current.b;
					resultA += current.a;
				}
				//Tada, we're done!
				sf::Color result = sf::Color(
					resultR / timesPoured,
					resultG / timesPoured,
					resultB / timesPoured,
					resultA / timesPoured
					);
				currentLiquid->SetColor(result);
			}
			else
			{
				liquidStream->SetActive(false);
			}
		}
		//Draw all of our everything
		Draw(window, view, viewUI, viewBev);
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
		case sf::Event::KeyReleased:
			switch (event.key.code)
			{

			default:
				break;
			}
			break;
		default:
			break;
		}
	}
}

void Game::Update(float deltaTime)
{
	//I think this is pretty obvious what this is doing.
	ObjectManager::UpdateObjects(deltaTime);
}

void Game::Draw(sf::RenderTarget & target, sf::View& view, sf::View& viewUI, sf::View& viewBev)
{
	target.clear(sf::Color::Cyan);

	sf::View viewLeft = view;
	viewLeft.setCenter(sf::Vector2f(140, 200));
	viewLeft.setViewport(sf::FloatRect(0, 0, 0.5f, 1));
	viewLeft.zoom(0.8f);

	sf::View viewRight = view;
	viewRight.setViewport(sf::FloatRect(0.5f, 0, 0.5f, 1));
	viewRight.zoom(1.4f);

	sf::View viewBeverages = viewBev;
	viewBeverages.setCenter(sf::Vector2f(480,0));
	viewBeverages.setViewport(sf::FloatRect(0.425f, 0, 0.15f, 1));

	target.setView(viewLeft);
	ObjectManager::DrawObjects(target, Scenes::SceneLeft);

	target.setView(viewRight);
	ObjectManager::DrawObjects(target, Scenes::SceneRight);

	target.setView(viewBeverages);
	ObjectManager::DrawObjects(target, Scenes::Beverages);

	//UI is drawn last, so we shove that right in your face
	target.setView(viewUI);
	ObjectManager::DrawObjects(target, Scenes::UI);
}
