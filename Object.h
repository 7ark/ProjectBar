#pragma once
#include "Common.h"
#include "ObjectManager.h"

class Object
{
public:
	std::string name = "Null";

	void Draw(sf::RenderTarget& target);
	virtual void Update(float deltaTime) {};

	void SetParent(Object* obj, bool adjustToLocal = true);
	Object* GetParent() { return parent; }

	const std::vector<Object*>& GetChildren() const
	{
		return children;
	}

	//Movement
	void SetPosition(sf::Vector2f pos) { transform.setPosition(pos.x, -pos.y); }
	sf::Vector2f GetPosition() { return sf::Vector2f(transform.getPosition().x,-transform.getPosition().y); }
	sf::Vector2f GetLocalPosition();
	void Translate(sf::Vector2f pos) { transform.move(pos); }

	void SetScale(sf::Vector2f scale) { transform.setScale(scale); }
	sf::Vector2f GetScale() { return transform.getScale(); }
	sf::Vector2f GetLocalScale();
	void Scale(sf::Vector2f scale) { transform.scale(scale); }

	void SetRotation(float angle) { transform.setRotation(angle); }
	float GetRotation() { return transform.getRotation(); }
	float GetLocalRotation();
	void Rotate(float angle) { transform.rotate(angle); }

	//Setters
	void SetActive(bool active) { if(!destroyed) enabled = active; }
	void SetVisible(bool vis) { visible = vis; }
	void SetLayer(int l) { layer = l; ObjectManager::UpdateLayerOrder(); }
	void SetScene(Scenes s) { scene = s; }
	virtual void Destroy();
	void DeleteObject();

	//Getters
	bool GetActive() { return enabled; }
	bool GetVisible() { return visible; }
	int GetUniqueID() { return id; }
	int GetLayer() { return layer; }
	Scenes GetScene() { return scene; }
	bool IsDestroyed() { return destroyed; }


	~Object();

protected:
	sf::Transformable transform;

	bool enabled = true;
	bool visible = true;
	bool destroyed = false;

	static int globalId;
	int id = 0;
	void NewID() { id = ++globalId; }
	int layer = 0;
	Scenes scene = Scenes::SceneAll;

	virtual void OnDraw(sf::RenderTarget& target, sf::Transformable& transform) = 0;

	Object* parent = nullptr;
	std::vector<Object*> children;

	Object();
};

