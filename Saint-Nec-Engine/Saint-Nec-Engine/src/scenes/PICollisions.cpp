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

	sne::GameObject *cube = createCube(_physicManager, center2, red);
	cube->setName("cube1");
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
	bigCubePO->setVelocity({-10, 0, 0});


	// Mass * 100
	glm::vec3 center2_1{-10, 0, 10};
	glm::vec3 center2_2{0, 0, 10};
	glm::vec3 center2_3{10, 0, 10};

	sne::GameObject *wall2 = createCube(_physicManager, center2_1, purple, true);
	wall2->setName("Wall2");
	addGameObject(wall2);

	sne::GameObject *cube2 = createCube(_physicManager, center2_2, red);
	cube2->setName("cube2");
	auto *cubePO2 = _physicManager.getLast();
	cubePO2->setAcceleration({0, 0, 0});
	addGameObject(cube2);

	sne::GameObject *bigCube2 = createCube(_physicManager, center2_3, purple);
	bigCube2->setName("bigCube2");
	auto *bigCubePO2 = _physicManager.getLast();
	bigCubePO2->setAcceleration({0, 0, 0});
	addGameObject(bigCube2);

	cubePO2->setMass(1.f);
	bigCubePO2->setMass(1000.f);
	bigCubePO2->setVelocity({-1., 0, 0});
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
