#pragma once
#include "Button.h"
#include "Text.h"

class Game;

class DisplayObject : public Button
{
public:
	DisplayObject();
	~DisplayObject();

	void Init(Textures const openImageTex, unsigned int const pageLength, char * const note[]);
	void Update(float deltaTime);

private:
	GameObject* openedImage;
	Text* displayTextLeft;
	Text* displayTextRight; 
	GameObject* changePageLeft;
	GameObject* changePageRight;

	void Clicked();
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
	
	static unsigned int pageSize;

	std::vector<char*> notes;
};

