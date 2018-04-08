#pragma once
#include "Common.h"

class Dialogue
{
public:
	Dialogue();
	~Dialogue();

	//So this will be loaded from json, for now we're giving it random shit
	void SetDialogue();

	std::vector<std::string> GetDialogue(DialogueOptions dialogue)
	{
		return dialogues[dialogue];
	}

private:
	std::map<DialogueOptions, std::vector<std::string>> dialogues;
};

