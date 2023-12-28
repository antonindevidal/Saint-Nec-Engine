#include "Game.hpp"

Game::Game(): sceneManager(sne::SceneManager::getInstance())
{
	FirstScene* scene = new FirstScene();
	sceneManager->addScene(scene);
	//sceneManager->changeScene(scene->getName());

	TerrainScene* terrainScene = new TerrainScene();
	terrainScene->setName("TerrainScene");
	sceneManager->addScene(terrainScene);

	GrassScene* grassScene = new GrassScene();
	grassScene->setName("GrassScene");
	sceneManager->addScene(grassScene);

	sceneManager->changeScene(grassScene->getName());


	
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

	UiHelper::WindowSceneTree(sne::SceneManager::getInstance());
}
