#include "ResourceManager.h"

void ResourceManager::Init()
{
	for (int i = 1; i < (int)Textures::Length; i++)
	{
		CreateTexture(texturePaths[i], (Textures)i);
	}
	for (int i = 1; i < (int)Fonts::Length; i++)
	{
		CreateFont(fontPaths[i], (Fonts)i);
	}
}

sf::Texture* ResourceManager::RetrieveTexture(Textures tex)
{
	if (tex == Textures::Null || tex == Textures::Length) 
	{
		std::cout << "ERROR: Attempted to retrieve invalid texture";
		return nullptr;
	}
	sf::Texture* returnedTexture = textures[tex];
	if (returnedTexture == nullptr)
	{
		returnedTexture = CreateTexture(texturePaths[(int)tex], tex);
	}
	return returnedTexture;
}

sf::Font * ResourceManager::RetrieveFont(Fonts font)
{
	if (font == Fonts::Null || font == Fonts::Length)
	{
		std::cout << "ERROR: Attempted to retrieve invalid font";
		return nullptr;
	}
	sf::Font* returnedFont = fonts[font];
	if (returnedFont == nullptr)
	{
		returnedFont = CreateFont(fontPaths[(int)font], font);
	}
	return returnedFont;
}

void ResourceManager::Destroy()
{

}

sf::Texture* ResourceManager::CreateTexture(std::string const & textureFile, Textures tex)
{
	sf::Texture* texture = new sf::Texture();
	if (!texture->loadFromFile(textureFile))
		std::cout << "ERROR: Cannot load texture " << textureFile;
	textures.insert(std::pair<Textures, sf::Texture*>(tex, texture));

	return texture;
}

sf::Font * ResourceManager::CreateFont(std::string const & fontFile, Fonts font)
{
	sf::Font* returnedFont = new sf::Font();
	if (!returnedFont->loadFromFile(fontFile))
		std::cout << "ERROR: Cannot load font " << fontFile;
	fonts.insert(std::pair<Fonts, sf::Font*>(font, returnedFont));

	return returnedFont;
}
