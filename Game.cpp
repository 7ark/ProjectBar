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

}

void Game::Update(float deltaTime)
{
	//std::cout << "Updating: " << deltaTime;
}

void Game::Draw(sf::RenderTarget & target)
{
	ObjectManager::DrawObjects(target);
}
