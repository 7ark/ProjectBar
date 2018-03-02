#pragma once
#include "Component.h"
#include "Game.h"

struct Key
{
	Key() {};
	Key(float t, Textures tex)
	{
		time = t;
		texture = Game::resourceManager.RetrieveTexture(tex);
	}
	float time;
	sf::Texture* texture;
};

class Animation : public Component
{
public:
	Animation();
	~Animation();

	void SetKeys(Key _keys[], int size);

	void Update(float deltaTime);

	void Play(bool loop = false);

	bool IsPlaying();

private:
	bool playing = false;
	bool looping = false;
	int currentKey = 0;
	sf::Clock timer;

	Key* keys = nullptr;
	int keysSize = 0;
};

