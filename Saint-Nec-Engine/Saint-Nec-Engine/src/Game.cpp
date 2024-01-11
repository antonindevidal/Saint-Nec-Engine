#include "Game.hpp"

Game::Game(): sceneManager(sne::SceneManager::getInstance())
{
	FirstScene* scene = new FirstScene();
	sceneManager->addScene(scene);
	//sceneManager->changeScene(scene->getName());

	TerrainScene* terrainScene = new TerrainScene();
	terrainScene->setName("TerrainScene");
	sceneManager->addScene(terrainScene);
	//sceneManager->changeScene(terrainScene->getName());

	PhysicScene* physicScene = new PhysicScene{};
	physicScene->setName("PhysicScene");
	sceneManager->addScene(physicScene);
	sceneManager->changeScene(physicScene->getName());

	PhysicScene2* physicScene2 = new PhysicScene2{};
	physicScene2->setName("physicScene2");
	sceneManager->addScene(physicScene2);
	sceneManager->changeScene(physicScene2->getName());
	
	
}

Game::~Game()
{
}

void Game::processInput(GLFWwindow* window, int mouseX, int mouseY)
{
	sceneManager->processInput(window, mouseX, mouseY);
}

void Game::update()
{
	sceneManager->update();
}

void Game::draw() const
{
	sceneManager->draw();

	UiHelper::WindowSceneManagerTree(sne::SceneManager::getInstance());
}
