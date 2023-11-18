#include "Game.hpp"

Game::Game(): sceneManager(sne::SceneManager::getInstance())
{
	FirstScene* scene = new FirstScene();
	sceneManager->addScene(scene);
	//sceneManager->changeScene(scene->getName());

	TerrainScene* terrainScene = new TerrainScene();
	terrainScene->setName("TerrainScene");
	sceneManager->addScene(terrainScene);
	sceneManager->changeScene(terrainScene->getName());


	
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
	ZoneScopedN("GameUpdate");
	sceneManager->update();
}

void Game::draw() const
{
	sceneManager->draw();

	UiHelper::WindowSceneTree(sne::SceneManager::getInstance()->getCurrentScene());
}
