#include "EPAScene.hpp"
#include "../ui_builder/UIBuilder.hpp"
#include "../Colors.hpp"

EPAScene::EPAScene()
{
}

void EPAScene::load()
{
	gameObjects = std::vector<sne::GameObject *>();

	glm::vec3 center{0, 0, 0},
		center2{-9, 10, 0},
		center3{0, 5, -4},
		center4{0, 2, 0},
		center5{-2, 0, 0};

	sne::GameObject *wall = createBox(_physicManager, center, blue, 3, 1, 1, true);
	wall->setName("Wall");
	addGameObject(wall);

	sne::GameObject *cube = createCube(_physicManager, center2, red);
	cube->setName("cube");
	auto *cubePO = _physicManager.getLast();
	cubePO->setAcceleration({0, 0, 0});
	cubePO->setVelocity({1, -1, 0});
	cubePO->setMass(1.f);
	addGameObject(cube);

	sne::GameObject *cube2 = createCube(_physicManager, center3, red);
	cube2->setName("cube2");
	auto *cube2PO = _physicManager.getLast();
	cube2PO->setAcceleration({0, 0, 0});
	cube2PO->setVelocity({0, -1, 1});
	cube2PO->setMass(1.f);
	addGameObject(cube2);

	sne::GameObject *cube3 = createCube(_physicManager, center4, purple);
	cube3->setName("cube3");
	auto *cube3PO = _physicManager.getLast();
	cube3PO->setAcceleration({0, 0, 0});
	cube3PO->setVelocity({0, -1, 0});
	cube3PO->setMass(1.f);
	addGameObject(cube3);


	// TO SHOW TO ALEXIS
	// sne::GameObject *cube4 = createCube(_physicManager, center5, purple);
	// cube4->setName("cube4");
	// auto *cube4PO = _physicManager.getLast();
	// cube4PO->setAcceleration({0, 0, 0});
	// cube4PO->setVelocity({1, 0, 0});
	// cube4PO->setMass(1.f);
	// addGameObject(cube4);
}

void EPAScene::unload()
{
	_physicManager.clear();
}

void EPAScene::update()
{
	sne::Scene::update();
	_physicManager.update();
}
