#include "Game.hpp"
#include "ui_helper/UiHelper.hpp"
#include "scenes/FirstScene.hpp"
#include "scenes/GrassScene.hpp"
#include "terrain/TerrainScene.hpp"
#include "scenes/PhysicScene.hpp"
#include "scenes/PhysicScene2.hpp"
#include "scenes/MouvementCoordination.hpp"

Game::Game(): sceneManager(sne::SceneManager::getInstance())
{
	auto* scene = new FirstScene();
	sceneManager->addScene(scene);

	TerrainScene* terrainScene = new TerrainScene();
	terrainScene->setName("TerrainScene");
	sceneManager->addScene(terrainScene);

	auto* grassScene = new GrassScene();
	grassScene->setName("GrassScene");
	sceneManager->addScene(grassScene);


	auto* physicScene = new PhysicScene{};
	physicScene->setName("PhysicScene");
	sceneManager->addScene(physicScene);

	auto* physicScene2 = new PhysicScene2{};
	physicScene2->setName("physicScene2");
	sceneManager->addScene(physicScene2);
	
	auto* mouvementCoordination = new MouvementCoordination{};
	mouvementCoordination->setName("mouvementCoordination");
	sceneManager->addScene(mouvementCoordination);

	auto* waterScene = new WaterGenerationScene();
	waterScene->setName("Water scene");
	sceneManager->addScene(waterScene);


	sceneManager->changeScene(waterScene->getName());
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
	sceneManager->drawUI();
}
