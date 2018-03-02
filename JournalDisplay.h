#pragma once
#include "Button.h"
#include "Text.h"

class JournalDisplay : public Button
{
public:
	JournalDisplay();
	~JournalDisplay();

	void Update(float deltaTime);

private:
	GameObject* openJournal;
	Text* displayTextLeft;
	Text* displayTextRight;

	void Clicked();
	void UpdatePage();
	void FlipPage(bool forward);

	int currentPage = 0;
	int fontSize = 23;
	
	static const unsigned int journalSize = 2;

	const char* notes[journalSize] =
	{
		"Humans: Weak creatures that love\nto kill shit\n\nDrinks They Enjoy: Any kind of beer\n\nPoisonous: Acid",
		"Animals: I don't know, I'm just\ntrying to fill up some of the space in this book.\n\nDrinks They Enjoy: Water???\n\nPoisonous: Literally everything"
	};
};

