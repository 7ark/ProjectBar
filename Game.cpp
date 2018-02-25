#include "Game.h"
#include "ObjectManager.h"
#include "Object.h"

ResourceManager Game::resourceManager;

Game::Game()
{
	resourceManager.Init();
	Setup();
}

Game::~Game()
{
	resourceManager.Destroy();
}

void Game::Setup()
{
	GameObject* obj1 = ObjectManager::CreateObject("Obj1", TextureName::Example, sf::Vector2f(20, 0));
	GameObject* obj2 = ObjectManager::CreateObject("Obj2", TextureName::Example, sf::Vector2f(-20, 0));
}

void Game::Update(float deltaTime)
{

}

void Game::Draw(sf::RenderTarget & target)
{
	ObjectManager::DrawObjects(target);
}
