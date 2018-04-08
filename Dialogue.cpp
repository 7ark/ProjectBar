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
			dialogues[(DialogueOptions)i].push_back("Test Dialogue #" + std::to_string(random));
		}
	}
}
