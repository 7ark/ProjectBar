#include "Button.h"
#include "Game.h"

void Button::Update(float deltaTime)
{
	if (!enabled) 
		return;
	sf::Vector2f pos = Game::window->mapPixelToCoords(sf::Mouse::getPosition(*Game::window));
	if (gameObject->GetSprite().getGlobalBounds().contains(pos))
	{
		if (!inBox)
		{
			if(pointerEnter.size() > 0)
				CallDelegate(pointerEnter);
			PointerEnter();
		}
		inBox = true;
	}
	else
	{
		if (inBox)
		{
			if(pointerExit.size() > 0)
				CallDelegate(pointerExit);
			PointerExit();
		}
		inBox = false;
	}
	if (inBox)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouseDown)
			canClick = true;
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouseDown && canClick)
		{
			if (!lockInMenu || (!gameObject->GetVisible() || !Game::menuOpen))
			{
				CallDelegate(click);
				Clicked();
			}
		}
		if(clickTexture != nullptr && mouseDown)
		gameObject->SetSprite(clickTexture);
	}
	if (!inBox || !mouseDown)
	{
		if (clickTexture != nullptr)
			gameObject->SetSprite(originalTexture);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		mouseDown = true;
	else 
	{
		mouseDown = false;
		canClick = false;
	}
	
}

void Button::SetHighlightShader(sf::Shader * shader, float thickness, sf::Color color)
{
	mat.SetShader(shader);
	mat.AddVec4Uniform("color", color);
	mat.AddCurrentTextureTypeUniform("texture", sf::Shader::CurrentTexture);
	shaderThickness = thickness;
}

void Button::CallDelegate(std::vector<std::function<void()>> const& del)
{
	for (auto&& call : del)
	{
		call();
	}
}

void Button::Clicked()
{
}

void Button::PointerEnter()
{
	if ((gameObject->GetVisible() && Game::menuOpen))
		return;
	if(highlightTexture != nullptr)
		gameObject->SetSprite(highlightTexture);
	if (mat.GetShader() != nullptr) 
	{
		mat.SetTexture(gameObject->GetMaterial()->GetTexture());
		mat.vec2Uniforms.clear();
		mat.AddVec2UniformThickness("thickness", sf::Vector2f(shaderThickness, shaderThickness));
		gameObject->SetShader(mat.GetShader());
		gameObject->GetMaterial()->vec2Uniforms = mat.vec2Uniforms;
		gameObject->GetMaterial()->vec4Uniforms = mat.vec4Uniforms;
		gameObject->GetMaterial()->currentTextureTypeUniforms = mat.currentTextureTypeUniforms;
	}
}

void Button::PointerExit()
{
	if (highlightTexture != nullptr)
		gameObject->SetSprite(originalTexture);
	if (mat.GetShader() != nullptr) 
	{
		gameObject->GetMaterial()->ClearAllUniforms();
		gameObject->SetShader(nullptr);
	}
}
