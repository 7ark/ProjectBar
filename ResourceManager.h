#pragma once
#include <unordered_map>
#include "Common.h"

enum class TextureName
{
	Null = 0,
	Bartender,
	BarBackground,
	BarCounter,

	Length
};

class ResourceManager
{
	const char* texturePaths[(int)TextureName::Length] =
	{
		"Null",
		"Textures/Bartender.png",
		"Textures/BarBackground.png",
		"Textures/BarCounter.png"
	};

public:
	void Init();
	sf::Texture* RetrieveTexture(TextureName tex);
	void Destroy();

private:
	std::unordered_map<TextureName, sf::Texture*> textures;

	sf::Texture* CreateTexture(std::string const& textureFile, TextureName tex);
};
