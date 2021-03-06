#include "DisplayObject.h"
#include "Button.h"
#include "GameObject.h"
#include "Game.h"

unsigned int DisplayObject::pageSize;

DisplayObject::DisplayObject()
{
	
}

void DisplayObject::Init(Textures const openJournalTex, unsigned int const pageLength, char * const note[])
{
	//Alright, this class is wacky. Forgive me.
	pageSize = pageLength;
	notes.clear();
	for (int i = 0; i < pageLength; i++)
	{
		notes.push_back(note[i]);
	}

	openedImage = ObjectManager::CreateObject("Open"+gameObject->name, Scenes::UI, openJournalTex);
	openedImage->SetLayer(10);
	openedImage->SetActive(false);

	displayTextLeft = ObjectManager::CreateText("TextLeft" + gameObject->name, Scenes::UI, Fonts::Hughs, notes[currentPage], sf::Vector2f(-150, -40));
	displayTextLeft->SetSize(fontSize);
	displayTextLeft->SetColor(sf::Color::Black);
	displayTextLeft->SetParent(openedImage);
	displayTextLeft->SetLayer(11);
	displayTextLeft->SetActive(false);

	displayTextRight = ObjectManager::CreateText("TextRight" + gameObject->name, Scenes::UI, Fonts::Hughs, notes[currentPage + 1], sf::Vector2f(250, -40));
	displayTextRight->SetSize(fontSize);
	displayTextRight->SetColor(sf::Color::Black);
	displayTextRight->SetParent(openedImage);
	displayTextRight->SetLayer(11);
	displayTextRight->SetActive(false);

	changePageLeft = ObjectManager::CreateObject("ChangePageLeft" + gameObject->name, Scenes::UI, Textures::ArrowDrawn, sf::Vector2f(-310, -190));
	changePageLeft->SetScale(sf::Vector2f(-0.05f, 0.05f));
	changePageLeft->SetParent(openedImage);
	changePageLeft->SetLayer(12);
	changePageLeft->SetActive(false);
	Button* leftButton = changePageLeft->AddComponent<Button>(Comp::Button);
	leftButton->lockInMenu = false;
	leftButton->pointerEnter.push_back(std::bind(&DisplayObject::HoverOnLeft, this));
	leftButton->pointerExit.push_back(std::bind(&DisplayObject::HoverOffLeft, this));
	leftButton->click.push_back(std::bind(&DisplayObject::FlipLeft, this));

	changePageRight = ObjectManager::CreateObject("ChangePageRight" + gameObject->name, Scenes::UI, Textures::ArrowDrawn, sf::Vector2f(310, -190));
	changePageRight->SetScale(sf::Vector2f(0.05f, 0.05f));
	changePageRight->SetParent(openedImage);
	changePageRight->SetLayer(12);
	changePageRight->SetActive(false);
	Button* rightButton = changePageRight->AddComponent<Button>(Comp::Button);
	rightButton->lockInMenu = false;
	rightButton->pointerEnter.push_back(std::bind(&DisplayObject::HoverOnRight, this));
	rightButton->pointerExit.push_back(std::bind(&DisplayObject::HoverOffRight, this));
	rightButton->click.push_back([this]() { FlipPage(true); });//  std::bind(&DisplayObject::FlipRight, this));

	UpdatePage();
}

void DisplayObject::HoverButton(GameObject * butt, bool hovering)
{
	float backwards = butt->GetScale().x < 0 ? -1 : 1;
	float h = hovering ? 2 : 1;
	butt->SetScale(sf::Vector2f(0.05f*h*backwards, 0.05f*h));
}

DisplayObject::~DisplayObject()
{

}



void DisplayObject::Update(float deltaTime)
{
	Button::Update(deltaTime);
}

void DisplayObject::Clicked()
{
	if (gameObject->GetVisible() && Game::menuOpen)
		return;
	gameObject->SetVisible(!gameObject->GetVisible());
	openedImage->SetActive(!gameObject->GetVisible());
	displayTextLeft->SetActive(!gameObject->GetVisible());
	displayTextRight->SetActive(!gameObject->GetVisible());
	changePageLeft->SetActive(!gameObject->GetVisible());
	changePageRight->SetActive(!gameObject->GetVisible());
	UpdatePage();

	if (!gameObject->GetVisible())
		Game::menuOpen = true;
	else
		Game::menuOpen = false;
}

void DisplayObject::UpdatePage()
{
	displayTextLeft->SetText(notes[currentPage], false);
	displayTextRight->SetText(notes[currentPage+1], false);

	if (!gameObject->GetVisible()) 
	{
		changePageLeft->SetActive(currentPage != 0);
		changePageRight->SetActive(currentPage != pageSize - 2);
	}
	else
	{
		changePageRight->SetActive(false);
		changePageLeft->SetActive(false);
	}
}

void DisplayObject::FlipPage(bool forward)
{
	if (forward)
	{
		currentPage = currentPage + 2 >= pageSize - 1 ? pageSize - 2 : currentPage + 2;
	}
	else
	{
		currentPage = currentPage - 2 < 0 ? 0 : currentPage - 2;
	}
	UpdatePage();
}
