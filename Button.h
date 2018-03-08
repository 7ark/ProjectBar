#pragma once
#include "Common.h"
#include "Component.h"
#include "Game.h"
#include "GameObject.h"
#include <functional>

class Button : public Component
{
public:
	std::vector<std::function<void()>> pointerEnter;
	std::vector<std::function<void()>> pointerExit;
	std::vector<std::function<void()>> click;
	void Update(float deltaTime);
	void SetHighlightTexture(Textures original, Textures highlight) 
	{
		originalTexture = Game::resourceManager.RetrieveTexture(original);
		highlightTexture = Game::resourceManager.RetrieveTexture(highlight); 
	}


	Button() {};
	~Button() { };
private:
	void CallDelegate(std::vector<std::function<void()>> const& del);
	sf::Texture* originalTexture;
	sf::Texture* highlightTexture;
protected:
	bool inBox = false;
	bool mouseDown = false;
	bool canClick = false;
	virtual void Clicked();
	virtual void PointerEnter();
	virtual void PointerExit();
};