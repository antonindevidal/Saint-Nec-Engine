#include "PhysicScene.hpp"
#include "../Colors.hpp"
#include "../ui_builder/UIBuilder.hpp"

PhysicScene::PhysicScene()
{
}

void PhysicScene::load()
{
	gameObjects = std::vector<sne::GameObject*>();

	glm::vec3 center{0,0,0 };
	sne::GameObject* cube = createCube(_physicManager, center, purple);
	_physicManager.getLast()->setAcceleration({ 0,0,0 });
	cube->setName("Cube violet");
	addGameObject(cube);


	glm::vec3 center2{ 2,0,0 }; 
	sne::GameObject* cube2 = createCube(_physicManager, center2, red);
	_physicManager.getLast()->setAcceleration({ 0,0,0 });
	_physicManager.getLast()->setVelocity({ -0.1,0,0});
	cube2->setName("Cube rouge");
	addGameObject(cube2);
}

void PhysicScene::unload()
{
	_physicManager.clear();
}

void PhysicScene::update()
{
	sne::Scene::update();
	_physicManager.update();
}
