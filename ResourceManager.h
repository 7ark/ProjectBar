#pragma once
#include <unordered_map>
#include "Common.h"

enum class Textures
{
	Null,
	Bartender,
	BarBackground,
	BarCounter,
	Journal,
	JournalHighlight,
	JournalOpen,
	Newspaper,
	NewspaperHighlight,
	ArrowDrawn,
	SignOpen,
	SignClosed,
	EmptySign,
	Tapper,
	GlassCup,
	Liquid,
	Frame,
	Man,

	Length
};

enum class Fonts
{
	Null,
	Hughs,

	Length
};

class ResourceManager
{
#pragma region Paths
	const char* texturePaths[(int)Textures::Length] =
	{
		"Null",
		"Textures/Bartender.png",
		"Textures/BarBackground.png",
		"Textures/BarCounter.png",
		"Textures/Journal.png",
		"Textures/JournalHighlight.png",
		"Textures/JournalOpen.png",
		"Textures/Newspaper.png",
		"Textures/NewspaperHighlight.png",
		"Textures/ArrowDrawn.png",
		"Textures/SignOpen.png",
		"Textures/SignClosed.png",
		"Textures/Sign.png",
		"Textures/Tapper.png",
		"Textures/GlassCup.png",
		"Textures/GlassCupLiquid.png",
		"Textures/BevFrame.png",
		"Textures/Races/Human/Man.png"
	};

	const char* fontPaths[(int)Fonts::Length] = 
	{
		"Null",
		"Fonts/Hughs.otf"
	};
#pragma endregion

public:
	void Init();
	sf::Texture* RetrieveTexture(Textures tex);
	sf::Font* RetrieveFont(Fonts font);
	void Destroy();

private:
	std::unordered_map<Textures, sf::Texture*> textures;
	std::unordered_map<Fonts, sf::Font*> fonts;

	sf::Texture* CreateTexture(std::string const& textureFile, Textures tex);
	sf::Font* CreateFont(std::string const& fontFile, Fonts font);
};
