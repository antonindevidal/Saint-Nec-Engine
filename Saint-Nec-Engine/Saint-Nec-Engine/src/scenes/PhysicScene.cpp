#include "PhysicScene.hpp"

PhysicScene::PhysicScene()
{
}

void PhysicScene::load()
{
	gameObjects = std::vector<sne::GameObject*>();

	sne::GameObject* cube = new sne::GameObject{};
	glm::vec3 center{0,0,0 };
	cube->addComponent(new sne::graphics::Cube("resources/shaders/color.vert", "resources/shaders/color.frag", glm::vec3{ 0.5,0.2,0.6 }));
	addGameObject(cube);
	sne::saintNecPhysics::PhysicObject* po1 = new sne::saintNecPhysics::PhysicObject{ center, 10 };
	sne::saintNecPhysics::BoxCollider * collider = new sne::saintNecPhysics::BoxCollider{ center, 1,1,1 };
	po1->setCollider(collider);
	po1->setAcceleration({ 0,0,0 });
	
	cube->addComponent(po1);
	cube->addComponent(collider);
	cube->setName("Cube viloet");
	_physicManager->addObject(po1);


	sne::GameObject* cube2 = new sne::GameObject{};
	glm::vec3 center2{ 2,0,0 };
	cube2->addComponent(new sne::graphics::Cube("resources/shaders/color.vert", "resources/shaders/color.frag", glm::vec3{ 0.9,0.2,0.2 }));
	cube2->translate(center2);
	addGameObject(cube2);
	sne::saintNecPhysics::PhysicObject* po2 = new sne::saintNecPhysics::PhysicObject{ center2, 10 };
	sne::saintNecPhysics::BoxCollider* collider2 = new sne::saintNecPhysics::BoxCollider{ center2, 1,1,1 };
	po2->setCollider(collider2);
	po2->setAcceleration({ 0,0,0 });
	po2->setVelocity({ -0.1,0,0});
	
	cube2->addComponent(po2);
	cube2->addComponent(collider2);
	cube2->setName("Cube rouge");
	_physicManager->addObject(po2);


}

void PhysicScene::unload()
{
	_physicManager->clear();
}

void PhysicScene::update()
{
	sne::Scene::update();
	_physicManager->update();
}
