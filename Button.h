#pragma once
#include "Common.h"
#include "Component.h"
#include "Game.h"
#include "GameObject.h"
#include <functional>

class Button : public Component
{
public:
	bool lockInMenu = true;
	std::vector<std::function<void()>> pointerEnter;
	std::vector<std::function<void()>> pointerExit;
	std::vector<std::function<void()>> click;
	void Update(float deltaTime);
	void SetHighlightTexture(Textures original, Textures highlight) 
	{
		originalTexture = Game::resourceManager.RetrieveTexture(original);
		highlightTexture = Game::resourceManager.RetrieveTexture(highlight); 
	}
	void SetClickTexture(Textures original, Textures click)
	{
		originalTexture = Game::resourceManager.RetrieveTexture(original);
		clickTexture = Game::resourceManager.RetrieveTexture(click);
	}
	void SetHighlightShader(sf::Shader* shader, float thickness = 1, sf::Color color = sf::Color::White);


	Button() {};
	~Button() { };
private:
	void CallDelegate(std::vector<std::function<void()>> const& del);
	sf::Texture* originalTexture = nullptr;
	sf::Texture* highlightTexture = nullptr;
	sf::Texture* clickTexture = nullptr;
	float shaderThickness = 0;
	Material mat;
protected:
	bool inBox = false;
	bool mouseDown = false;
	bool canClick = false;
	virtual void Clicked();
	virtual void PointerEnter();
	virtual void PointerExit();
};