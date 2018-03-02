#include "JournalDisplay.h"
#include "Button.h"
#include "GameObject.h"


JournalDisplay::JournalDisplay()
{
}


JournalDisplay::~JournalDisplay()
{
}

void JournalDisplay::Clicked()
{
	gameObject->SetVisible(!gameObject->GetVisible());
}
