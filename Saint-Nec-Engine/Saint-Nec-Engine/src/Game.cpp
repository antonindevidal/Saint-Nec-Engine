#include "Game.hpp"

Game::Game(): sceneManager(sne::SceneManager::getInstance())
{
	sne::Scene* scene = new sne::Scene("Scene1");

	sceneManager->addScene(scene);
	sceneManager->changeScene(scene->getName());

	sne::GameObject* cube = new sne::GameObject();
	scene->addGameObject(cube);

	cube->addComponent(new sne::graphics::Cube("resources/shaders/basic.vert", "resources/shaders/basic.frag"));


}

Game::~Game()
{
}

void Game::update()
{
	sceneManager->update();
}

void Game::draw() const
{
	sceneManager->draw();
}
