#include "Game.hpp"

Game::Game(): sceneManager(sne::SceneManager::getInstance())
{
	FirstScene* scene = new FirstScene();
	sceneManager->addScene(scene);
	sceneManager->changeScene(scene->getName());

	
}

Game::~Game()
{
}

void Game::processInput(GLFWwindow* window)
{
	sceneManager->processInput(window);
}

void Game::update()
{
	sceneManager->update();
}

void Game::draw() const
{
	sceneManager->draw();

	UiHelper::WindowSceneTree(sne::SceneManager::getInstance()->getCurrentScene());
}
