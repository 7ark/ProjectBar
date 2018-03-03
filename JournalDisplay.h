#pragma once
#include "Button.h"
#include "Text.h"

class Game;

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
	GameObject* changePageLeft;
	GameObject* changePageRight;

	void Clicked();
	void PointerEnter();
	void PointerExit();
	void UpdatePage();
	void FlipPage(bool forward);
	void HoverButton(GameObject* butt, bool hovering);

	//Callback Functions
	void HoverOnLeft() { HoverButton(changePageLeft, true); };
	void HoverOffLeft() { HoverButton(changePageLeft, false); };
	void HoverOnRight() { HoverButton(changePageRight, true); };
	void HoverOffRight() { HoverButton(changePageRight, false); };
	void FlipRight() { FlipPage(true); }
	void FlipLeft() { FlipPage(false); }

	int currentPage = 0;
	int fontSize = 23;
	
	static const unsigned int journalSize = 4;

	const char* notes[journalSize] =
	{
		"Humans: Weak creatures that love\nto kill shit\n\nDrinks They Enjoy: Any kind of beer\n\nPoisonous: Acid",
		"Animals: I don't know, I'm just\ntrying to fill up some of the space in this book.\n\nDrinks They Enjoy: Water???\n\nPoisonous: Literally everything",
		"Something else: I'm just trying to fill\npages at this point to be honest.\n\nDrinks They Enjoy: Who?? \nThis isn't very specific\n\nPoisonous: Memes",
		"Manpat: Best god damn #other-dev dude.\n\nDrinks They Enjoy: sarsaparilla and \norange juice\n\nPoisonous: Everything humans die from"
	};
};

