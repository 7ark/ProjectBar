#pragma once
#include "Component.h"
#include "Game.h"

struct Key
{
	Key() {};
	Key(float t, Textures tex, sf::Vector2f s = sf::Vector2f(1,1))
	{
		time = t;
		texture = Game::resourceManager.RetrieveTexture(tex);
		scale = s;
	}
	Key(Textures tex, sf::Vector2f s = sf::Vector2f(1, 1))
	{
		time = 0;
		texture = Game::resourceManager.RetrieveTexture(tex);
		scale = s;
	}
	float time;
	sf::Texture* texture;
	sf::Vector2f scale;
};

class Animation : public Component
{
public:
	Animation();
	~Animation();

	void SetKeys(Key _keys[], int size);
	void SetConstantTime(float t);

	void Update(float deltaTime);

	void Play(bool loop = false);
	void Stop();

	bool IsPlaying();

private:
	bool setScaleYet = false;

	bool playing = false;
	bool looping = false;
	int currentKey = 0;
	float timer = 0;

	Key* keys = nullptr;
	int keysSize = 0;
	sf::Vector2f originalScale;
};

