#include "JournalDisplay.h"
#include "Button.h"
#include "GameObject.h"
#include "Game.h"

const unsigned int JournalDisplay::journalSize;

JournalDisplay::JournalDisplay()
{
	openJournal = ObjectManager::CreateObject("OpenJournal", Textures::JournalOpen);
	openJournal->SetLayer(10);
	openJournal->SetActive(false);

	displayTextLeft = ObjectManager::CreateText("JournalTextLeft", Fonts::Hughs, notes[currentPage], sf::Vector2f(-360,220));
	displayTextLeft->SetSize(fontSize);
	displayTextLeft->SetColor(sf::Color::Black);
	displayTextLeft->SetParent(openJournal);
	displayTextLeft->SetLayer(11);
	displayTextLeft->SetActive(false);

	displayTextRight = ObjectManager::CreateText("JournalTextRight", Fonts::Hughs, notes[currentPage+1], sf::Vector2f(0, 220));
	displayTextRight->SetSize(fontSize);
	displayTextRight->SetColor(sf::Color::Black);
	displayTextRight->SetParent(openJournal);
	displayTextRight->SetLayer(11);
	displayTextRight->SetActive(false);

	changePageLeft = ObjectManager::CreateObject("ChangePageLeft", Textures::ArrowDrawn, sf::Vector2f(-310, -190));
	changePageLeft->SetScale(sf::Vector2f(-0.05f, 0.05f));
	changePageLeft->SetParent(openJournal);
	changePageLeft->SetLayer(12);
	changePageLeft->SetActive(false);
	Button* leftButton = changePageLeft->AddComponent<Button>(Comp::Button);
	leftButton->pointerEnter.push_back(std::bind(&JournalDisplay::HoverOnLeft, this));
	leftButton->pointerExit.push_back(std::bind(&JournalDisplay::HoverOffLeft, this));
	leftButton->click.push_back(std::bind(&JournalDisplay::FlipLeft, this));

	
	changePageRight = ObjectManager::CreateObject("ChangePageRight", Textures::ArrowDrawn, sf::Vector2f(310, -190));
	changePageRight->SetScale(sf::Vector2f(0.05f, 0.05f));
	changePageRight->SetParent(openJournal);
	changePageRight->SetLayer(12);
	changePageRight->SetActive(false);
	Button* rightButton = changePageRight->AddComponent<Button>(Comp::Button);
	rightButton->pointerEnter.push_back(std::bind(&JournalDisplay::HoverOnRight, this));
	rightButton->pointerExit.push_back(std::bind(&JournalDisplay::HoverOffRight, this));
	rightButton->click.push_back(std::bind(&JournalDisplay::FlipRight, this));
}

void JournalDisplay::HoverButton(GameObject * butt, bool hovering)
{
	float backwards = butt->GetScale().x < 0 ? -1 : 1;
	float h = hovering ? 2 : 1;
	butt->SetScale(sf::Vector2f(0.05f*h*backwards, 0.05f*h));
}

JournalDisplay::~JournalDisplay()
{

}

void JournalDisplay::Update(float deltaTime)
{
	Button::Update(deltaTime);
}

void JournalDisplay::Clicked()
{
	gameObject->SetVisible(!gameObject->GetVisible());
	openJournal->SetActive(!gameObject->GetVisible());
	displayTextLeft->SetActive(!gameObject->GetVisible());
	displayTextRight->SetActive(!gameObject->GetVisible());
	changePageLeft->SetActive(!gameObject->GetVisible());
	changePageRight->SetActive(!gameObject->GetVisible());
}

void JournalDisplay::PointerEnter()
{
	gameObject->SetSprite(Game::resourceManager.RetrieveTexture(Textures::JournalHighlight));
}

void JournalDisplay::PointerExit()
{
	gameObject->SetSprite(Game::resourceManager.RetrieveTexture(Textures::Journal));
}

void JournalDisplay::UpdatePage()
{
	displayTextLeft->SetText(notes[currentPage]);
	displayTextRight->SetText(notes[currentPage+1]);
}

void JournalDisplay::FlipPage(bool forward)
{
	if (forward)
	{
		currentPage = currentPage + 2 >= journalSize - 1 ? journalSize - 2 : currentPage + 2;
	}
	else
	{
		currentPage = currentPage - 2 < 0 ? 0 : currentPage - 2;
	}
	UpdatePage();
}
