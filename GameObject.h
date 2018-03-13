#pragma once
#include "Common.h"
#include "ObjectManager.h"
#include "Object.h"
#include "Material.h"
#include "Component.h"

class Game;

class GameObject : public Object
{
public:
	GameObject();
	void Init(std::string name, Textures const & textureName, sf::Vector2f position = sf::Vector2f(0, 0));

	void Update(float deltaTime);
	void Destroy();

	//Getters
	sf::Sprite GetSprite() { return sprite; }
	Material* GetMaterial() { return &material; }
	sf::Color GetColor() { return sprite.getColor(); }
	FillMode GetFillMode() { return fillMode; }
	float GetFillAmount() { return currentFillAmount; }

	//Setters
	void SetSprite(sf::Texture* texture, bool centered = true);
	void SetColor(sf::Color color) { sprite.setColor(color); }
	void SetMaterial(Material mat) { material = mat; }
	void SetShader(sf::Shader* shader) { material.SetShader(shader); }
	void SetFillMode(FillMode mode) { fillMode = mode; }
	void SetFillAmount(float fillAmount);
	void ChangeFillAmount(float amount) { SetFillAmount(currentFillAmount + amount); }

	template<class T>
	T* AddComponent(Comp componentType)
	{
		components.push_back(std::make_unique<T>());
		Component* result = components.back().get();
		result->gameObject = this;
		result->componentType = componentType;
		return (T*)result;
	}

	template<class T>
	T* GetComponent(Comp componentType)
	{
		for (size_t i = 0; i < components.size(); i++)
		{
			if (components[i].get()->componentType == componentType)
				return (T*)components[i].get();
		}
		return nullptr;
	}

	template<class T>
	std::vector<T*> GetComponents(Comp componentType)
	{
		std::vector<T*> result;
		for (size_t i = 0; i < components.size(); i++)
		{
			if (components[i].get()->componentType == componentType)
				result.push_back((T*)components[i].get());
		}
		return result;
	}

protected:
	sf::Sprite sprite;
	Material material;
	FillMode fillMode = FillMode::None;
	float currentFillAmount = 1;

	std::vector<std::unique_ptr<Component>> components;

	virtual void OnDraw(sf::RenderTarget& target, sf::Transformable& transform);
	
};


