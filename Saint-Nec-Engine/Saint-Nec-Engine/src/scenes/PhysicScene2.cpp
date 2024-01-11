#include "PhysicScene.hpp"

PhysicScene::PhysicScene()
{
}

void PhysicScene::load()
{
	gameObjects = std::vector<sne::GameObject *>();

	glm::vec3 center{0, 0, 0};
	sne::GameObject *cube = new sne::GameObject{};
	cube->setName("Cube violet");

	cube->addComponent(new sne::graphics::Cube("resources/shaders/color.vert", "resources/shaders/color.frag", glm::vec3{0.5, 0.2, 0.6}));

	sne::physics::PhysicObject *po1 = new sne::physics::PhysicObject{center, 10};
	po1->setCollider(new sne::physics::BoxCollider{center, 1, 1, 1});

	cube->addComponent(po1);
	
	_physicManager.addObject(po1);

	addGameObject(cube);
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
