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

void Animation::SetConstantTime(float t)
{
	for (size_t i = 0; i < keysSize-1; i++)
	{
		keys[i].time = t;
	}
}

void Animation::Update(float deltaTime)
{
	if (gameObject == nullptr) return;

	if (!setScaleYet)
	{
		originalScale = gameObject->GetScale();
		setScaleYet = true;
	}

	//I was doing += deltaTime, but it has a weird delay or parts of it slows down??
	//I'm not really sure why, but it looks fine at a constant... could be an issue in the future. I'll have to see.
	//Also might look fine with an actual animation rather than changing the scale
	if (playing)
		timer += 0.001f;
	else
		timer = 0;
	
	//Are we ready to... change our frame of the animation
	if (playing && keysSize != 0 && timer >= keys[currentKey].time)
	{
		if (currentKey == keysSize-1)
		{
			if (looping)
				currentKey = 0;
			else
				playing = false;
		}
		else
			currentKey++;

		gameObject->SetSprite(keys[currentKey].texture);
		sf::Vector2f newScale = sf::Vector2f(originalScale.x*keys[currentKey].scale.x, originalScale.y*keys[currentKey].scale.y);
		gameObject->SetScale(newScale);
		timer = 0;
	}

}

void Animation::Play(bool loop)
{
	looping = loop;
	playing = true;
	currentKey = 0;
	timer = 0;
}

void Animation::Stop()
{
	looping = false;
	playing = false;
}

bool Animation::IsPlaying()
{
	return playing;
}
