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
	TapperButtonUp,
	TapperButtonDown,
	Man,

	Length
};

enum class Fonts
{
	Null,
	Hughs,

	Length
};

enum class Shaders
{
	Null,
	Outline,

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
		"Textures/TapperButtonUp.png",
		"Textures/TapperButtonDown.png",
		"Textures/Races/Human/Man.png"
	};

	const char* fontPaths[(int)Fonts::Length] = 
	{
		"Null",
		"Fonts/Hughs.otf"
	};

	const char* shaderPaths[(int)Shaders::Length] =
	{
		"Null",
		"Shaders/Outline.frag"
	};
#pragma endregion

public:
	void Init();
	sf::Texture* RetrieveTexture(Textures tex);
	sf::Font* RetrieveFont(Fonts font);
	sf::Shader* RetrieveShader(Shaders shader, sf::Shader::Type shaderType);

private:
	std::unordered_map<Textures, sf::Texture*> textures;
	std::unordered_map<Fonts, sf::Font*> fonts;
	std::unordered_map<Shaders, sf::Shader*> shaders;

	sf::Texture* CreateTexture(std::string const& textureFile, Textures tex);
	sf::Font* CreateFont(std::string const& fontFile, Fonts font);
	sf::Shader* CreateShader(std::string const& shaderFile, sf::Shader::Type shaderType, Shaders shader);
};
