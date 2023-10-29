#include "Game.hpp"

Game::Game(): sceneManager()
{
	sne::Scene* scene = new sne::Scene("Scene1");
	sne::GameObject* cube = new sne::GameObject();

	cube->addComponent(new sne::graphics::Cube());
	scene->addGameObject(cube);

	sceneManager.addScene(scene);
	sceneManager.changeScene(scene->getName());

}

Game::~Game()
{
}

void Game::update()
{
	sceneManager.update();
}

void Game::draw() const
{
	sceneManager.draw();
}
