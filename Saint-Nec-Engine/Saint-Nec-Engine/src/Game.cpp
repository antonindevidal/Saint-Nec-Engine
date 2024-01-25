#include "Game.hpp"
#include "ui_helper/UiHelper.hpp"
#include "scenes/FirstScene.hpp"
#include "scenes/GrassScene.hpp"
#include "terrain/TerrainScene.hpp"
#include "scenes/PhysicScene.hpp"
#include "scenes/PhysicScene2.hpp"
#include "scenes/MouvementCoordination.hpp"
#include "scenes/PICollisions.hpp"

Game::Game(): sceneManager(sne::SceneManager::getInstance())
{
	auto* scene = new FirstScene();
	sceneManager->addScene(scene);
	//sceneManager->changeScene(scene->getName());

	TerrainScene* terrainScene = new TerrainScene();
	terrainScene->setName("TerrainScene");
	sceneManager->addScene(terrainScene);
	//sceneManager->changeScene(terrainScene->getName());

	auto* grassScene = new GrassScene();
	grassScene->setName("GrassScene");
	sceneManager->addScene(grassScene);

	sceneManager->changeScene(grassScene->getName());

	auto* physicScene = new PhysicScene{};
	physicScene->setName("PhysicScene");
	sceneManager->addScene(physicScene);
	sceneManager->changeScene(physicScene->getName());

	auto* physicScene2 = new PhysicScene2{};
	physicScene2->setName("physicScene2");
	sceneManager->addScene(physicScene2);
	sceneManager->changeScene(physicScene2->getName());
	
	auto* mouvementCoordination = new MouvementCoordination{};
	mouvementCoordination->setName("mouvementCoordination");
	sceneManager->addScene(mouvementCoordination);
	sceneManager->changeScene(mouvementCoordination->getName());

	auto* piCollisions = new PICollisions{};
	piCollisions->setName("PI Collisions counter");
	sceneManager->addScene(piCollisions);
	sceneManager->changeScene(piCollisions->getName());
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
