#include "PICollisions.hpp"
#include "../ui_builder/UIBuilder.hpp"
#include "../Colors.hpp"


PICollisions::PICollisions()
{
}

void PICollisions::load()
{
	gameObjects = std::vector<sne::GameObject *>();

	// Same mass
	glm::vec3 center{-10, 0, 0};
	glm::vec3 center2{0, 0, 0};
	glm::vec3 center3{10, 0, 0};

	sne::GameObject *wall = createCube(_physicManager, center, blue, true);
	wall->setName("Wall");
	addGameObject(wall);

	sne::GameObject *cube = createCube(_physicManager, center2, blue);
	cube->setName("cube");
	auto *cubePO = _physicManager.getLast();
	cubePO->setAcceleration({0, 0, 0});
	addGameObject(cube);

	sne::GameObject *bigCube = createCube(_physicManager, center3, blue);
	bigCube->setName("bigCube");
	auto *bigCubePO = _physicManager.getLast();
	bigCubePO->setAcceleration({0, 0, 0});
	addGameObject(bigCube);

	cubePO->setMass(1.f);
	bigCubePO->setMass(1.f);
	bigCubePO->setVelocity({-1, 0, 0});


	// Mass * 100
	glm::vec3 center100{-10, 0, 10};
	glm::vec3 center100_2{0, 0, 10};
	glm::vec3 center100_3{10, 0, 10};

	sne::GameObject *wall100 = createCube(_physicManager, center100, purple, true);
	wall100->setName("Wall100");
	addGameObject(wall100);

	sne::GameObject *cube100 = createCube(_physicManager, center100_2, purple);
	cube100->setName("cube100");
	auto *cubePO100 = _physicManager.getLast();
	cubePO100->setAcceleration({0, 0, 0});
	addGameObject(cube100);

	sne::GameObject *bigCube100 = createCube(_physicManager, center100_3, purple);
	bigCube100->setName("bigCube100");
	auto *bigCubePO100 = _physicManager.getLast();
	bigCubePO100->setAcceleration({0, 0, 0});
	addGameObject(bigCube100);

	cubePO100->setMass(1.f);
	bigCubePO100->setMass(100.f);
	bigCubePO100->setVelocity({-1, 0, 0});
}

void PICollisions::unload()
{
	_physicManager.clear();
}

void PICollisions::update()
{
	sne::Scene::update();
	_physicManager.update();
}
