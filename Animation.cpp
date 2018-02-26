#include "Animation.h"
#include <math.h>
#include "GameObject.h"


Animation::Animation()
{
}


Animation::~Animation()
{
	if (keys != nullptr)
		delete[] keys;
}

void Animation::SetKeys(Key _keys[], int size)
{
	keysSize = size;
	if (keys != nullptr)
		delete[] keys;
	keys = new Key[size];
	for (size_t i = 0; i < size; i++)
	{
		keys[i] = _keys[i];
	}
}

void Animation::Update(float deltaTime)
{
	if (playing && keysSize != 0 && abs(keys[currentKey].time - timer.getElapsedTime().asSeconds()) < 0.01f)
	{
		if (currentKey == keysSize-1)
		{
			timer.restart();
			if (looping)
				currentKey = 0;
			else
				playing = false;
		}
		else
			currentKey++;
		gameObject->SetSprite(keys[currentKey].texture);
	}

}

void Animation::Play(bool loop)
{
	looping = loop;
	playing = true;
	currentKey = 0;
	timer.restart();
}

bool Animation::IsPlaying()
{
	return playing;
}
