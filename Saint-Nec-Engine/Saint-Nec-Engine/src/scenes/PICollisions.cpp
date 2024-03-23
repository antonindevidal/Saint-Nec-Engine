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
	glm::vec3 center{-30, 0, 20};
	glm::vec3 center2{0, 0, 0};
	glm::vec3 center3{10, 0, 0};

	sne::GameObject *wall = createBox(_physicManager, center, blue, 30, 10, 50, true);
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
	bigCubePO->setVelocity({-1, 0, 0});

	// Mass * 100
	glm::vec3 center2_1{-10, 0, 10};
	glm::vec3 center2_2{0, 0, 10};
	glm::vec3 center2_3{10, 0, 10};

	sne::GameObject *cube2 = createCube(_physicManager, center2_2, red);
	cube2->setName("cube2");
	auto *cubePO2 = _physicManager.getLast();
	cubePO2->setAcceleration({0, 0, 0});
	addGameObject(cube2);

	sne::GameObject *bigCube2 = createCube(_physicManager, center2_3, purple, false, 2);
	bigCube2->setName("bigCube2");
	auto *bigCubePO2 = _physicManager.getLast();
	bigCubePO2->setAcceleration({0, 0, 0});
	addGameObject(bigCube2);

	cubePO2->setMass(1.f);
	bigCubePO2->setMass(100.f);
	bigCubePO2->setVelocity({-1., 0, 0});

	// Mass * 10000
	glm::vec3 center3_1{-10, 0, 20};
	glm::vec3 center3_2{0, 0, 20};
	glm::vec3 center3_3{10, 0, 20};

	sne::GameObject *cube3 = createCube(_physicManager, center3_2, red, false, 1);
	cube3->setName("cube3");
	auto *cubePO3 = _physicManager.getLast();
	cubePO3->setAcceleration({0, 0, 0});
	addGameObject(cube3);

	sne::GameObject *bigCube3 = createCube(_physicManager, center3_3, purple, false, 5);
	bigCube3->setName("bigCube3");
	auto *bigCubePO3 = _physicManager.getLast();
	bigCubePO3->setAcceleration({0, 0, 0});
	addGameObject(bigCube3);

	cubePO3->setMass(1.f);
	bigCubePO3->setMass(10000.f);
	bigCubePO3->setVelocity({-1., 0, 0});

	// sphere qui tombe
	glm::vec3 centerSphere{-30, 15, 20};
	sne::GameObject *sphere = createSphere(_physicManager, centerSphere, false, 0.5);
	sphere->setName("sphere");
	auto *spherePO = _physicManager.getLast();
	spherePO->setAcceleration({0, -9.81, 0});
	// spherePO->setVelocity({0, -1, 0});
	addGameObject(sphere);

	// // Vase + sphere
	// glm::vec3 centerContainer{-30, 15, 20};
	// sne::GameObject *container = createBox(_physicManager, centerContainer, red, 30, 10, 50, true);
	// container->setName("centerContainer");
	// auto *containerPO = _physicManager.getLast();
	// containerPO->setAcceleration({0, 0, 0});
	// addGameObject(container);
}

void PICollisions::unload()
{
	_physicManager.clear();
}

void PICollisions::update()
{
	lastUpdate += Time::getDeltaTime();
	if (lastUpdate > 2)
	{
		lastUpdate = 0;
		// sphere qui tombe
		float x,y;
		x = cos((2+counter)*3.14 / (1+(counter%3)));
		y = sin((2+counter)*3.14 / (1+(counter%3)));
		glm::vec3 centerSphere{-30+x, 15, 20+y};
		sne::GameObject *sphere = createSphere(_physicManager, centerSphere, false, 0.5);
		sphere->setName("sphere");
		auto *spherePO = _physicManager.getLast();
		spherePO->setAcceleration({0, -9.81, 0});
		addGameObject(sphere);
		counter++;
	}

	sne::Scene::update();
	_physicManager.update();
}
