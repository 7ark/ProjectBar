#include "Dialogue.h"



Dialogue::Dialogue()
{
}


Dialogue::~Dialogue()
{
}

void Dialogue::SetDialogue()
{
	for (int i = 0; i < (int)DialogueOptions::Length; i++)
	{
		for (int j = 0; j < (rand() % 3)+5; j++)
		{
			int random = rand();
			optionDialogues[(DialogueOptions)i].push_back("Test Dialogue #" + std::to_string(random));
		}
	}

	for (int i = 0; i < (int)CustomerReaction::Length; i++)
	{
		for (int j = 0; j < (rand() % 3) + 5; j++)
		{
			int random = rand();
			reactionDialogues[(CustomerReaction)i].push_back("Test Reaction Dialogue #" + std::to_string(random));
		}
	}
}
