#include "JournalDisplay.h"
#include "Button.h"
#include "GameObject.h"

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
}

JournalDisplay::~JournalDisplay()
{
	delete notes;
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
		currentPage = currentPage + 2 > journalSize ? journalSize - 1 : currentPage + 2;
	}
	else
	{
		currentPage = currentPage - 2 < 0 ? 0 : currentPage - 2;
	}
	UpdatePage();
}
