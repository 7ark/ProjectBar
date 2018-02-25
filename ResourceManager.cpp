#include "ResourceManager.h"

void ResourceManager::Init()
{
	for (int i = 1; i < (int)TextureName::Length; i++)
	{
		CreateTexture(TexturePaths[i], (TextureName)i);
	}
}

sf::Texture* ResourceManager::RetrieveTexture(TextureName tex)
{
	if (tex == TextureName::Null || tex == TextureName::Length) 
	{
		std::cout << "ERROR: Attempted to retrieve invalid texture";
		return nullptr;
	}
	sf::Texture* returnedTexture = textures[tex];
	if (returnedTexture == nullptr)
	{
		returnedTexture = CreateTexture(TexturePaths[(int)tex], tex);
	}
	return returnedTexture;
}

void ResourceManager::Destroy()
{
	delete TexturePaths;
}

sf::Texture* ResourceManager::CreateTexture(std::string const & textureFile, TextureName tex)
{
	sf::Texture* texture = new sf::Texture();
	if (!texture->loadFromFile(textureFile))
		std::cout << "ERROR: Cannot load texture " << textureFile;
	textures.insert(std::pair<TextureName, sf::Texture*>(tex, texture));

	return texture;
}
