#pragma once
#include <unordered_map>
#include "Common.h"

enum class TextureName
{
	Null = 0,
	Example,

	Length
};

class ResourceManager
{
	std::string* TexturePaths = new std::string[3]
	{
		"Null",
		"Textures\\Example.png",
		"Length"
	};

public:
	void Init();
	sf::Texture* RetrieveTexture(TextureName tex);
	void Destroy();

private:
	std::unordered_map<TextureName, sf::Texture*> textures;

	sf::Texture* CreateTexture(std::string const& textureFile, TextureName tex);
};
