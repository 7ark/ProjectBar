#pragma once
#include <unordered_map>
#include "Common.h"

enum class TextureName
{
	Null = 0,
	Example,
	run1,
	run2,
	run3,
	run4,
	run5,
	run6,

	Length
};

class ResourceManager
{
	const char* texturePaths[(int)TextureName::Length] =
	{
		"Null",
		"Textures//Example.png",
		"Textures//run1.png",
		"Textures//run2.png",
		"Textures//run3.png",
		"Textures//run4.png",
		"Textures//run5.png",
		"Textures//run6.png"
	};

public:
	void Init();
	sf::Texture* RetrieveTexture(TextureName tex);
	void Destroy();

private:
	std::unordered_map<TextureName, sf::Texture*> textures;

	sf::Texture* CreateTexture(std::string const& textureFile, TextureName tex);
};
