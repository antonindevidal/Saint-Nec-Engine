#include "PhysicScene.hpp"
#include "../Colors.hpp"
#include "../ui_builder/UIBuilder.hpp"

PhysicScene::PhysicScene()
{
}

void PhysicScene::load()
{
	gameObjects = std::vector<sne::GameObject *>();

	glm::vec3 center{0, 0, 0};
	sne::GameObject *cube = createCube(_physicManager, center, purple);
	_physicManager.getLast()->setAcceleration({0, 0, 0});
	cube->setName("Cube violet");
	addGameObject(cube);

	glm::vec3 center2{2, 0, 0};
	sne::GameObject *cube2 = createCube(_physicManager, center2, red);
	_physicManager.getLast()->setAcceleration({0, 0, 0});
	_physicManager.getLast()->setVelocity({-0.1, 0, 0});
	cube2->setName("Cube rouge");
	addGameObject(cube2);

	glm::vec3 centerSphere1{4, 0, 5};
	sne::GameObject *sphere = createSphere(_physicManager, centerSphere1, false, 0.5);
	sphere->setName("sphere");
	auto *spherePO = _physicManager.getLast();
	spherePO->setAcceleration({0, 0, 0});
	addGameObject(sphere);

	glm::vec3 centerSphere2{0, 0, 5};
	sne::GameObject *sphere2 = createSphere(_physicManager, centerSphere2, false, 0.5);
	sphere2->setName("sphere2");
	auto *spherePO2 = _physicManager.getLast();
	spherePO2->setAcceleration({0, 0, 0});
	spherePO2->setVelocity({0.1, 0, 0});
	addGameObject(sphere2);
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
