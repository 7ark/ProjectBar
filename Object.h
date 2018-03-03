#pragma once
#include "Common.h"
#include "ObjectManager.h"

class Object
{
public:
	std::string name = "Null";

	void draw(sf::RenderTarget& target);
	virtual void Update(float deltaTime) {};

	void SetParent(Object* obj);

	const std::vector<Object*>& GetChildren() const
	{
		return children;
	}

	//Movement
	void SetPosition(sf::Vector2f pos) { transform.setPosition(pos.x, -pos.y); }
	sf::Vector2f GetPosition() { return transform.getPosition(); }
	void Translate(sf::Vector2f pos) { transform.move(pos); }

	void SetScale(sf::Vector2f scale) { transform.setScale(scale); }
	sf::Vector2f GetScale() { return transform.getScale(); }
	void Scale(sf::Vector2f scale) { transform.scale(scale); }

	void SetRotation(float angle) { transform.setRotation(angle); }
	float GetRotation() { transform.getRotation(); }
	void Rotate(float angle) { transform.rotate(angle); }


	//Setters
	void SetActive(bool active) { enabled = active; }
	void SetVisible(bool vis) { visible = vis; }
	void SetLayer(int l) { layer = l; ObjectManager::UpdateLayerOrder(); }

	//Getters
	bool GetActive() { return enabled; }
	bool GetVisible() { return visible; }
	int GetUniqueID() { return id; }
	int GetLayer() { return layer; }


	~Object();

protected:
	sf::Transformable transform;

	bool enabled = true;
	bool visible = true;

	static int globalId;
	int id = 0;
	void NewID() { id = ++globalId; }
	int layer = 0;

	virtual void onDraw(sf::RenderTarget& target, sf::Transformable& transform) = 0;

	Object* parent = nullptr;
	std::vector<Object*> children;

	Object();
};

