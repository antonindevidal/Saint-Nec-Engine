#include "PhysicScene2.hpp"

PhysicScene2::PhysicScene2()
{
}

void PhysicScene2::load()
{
	gameObjects = std::vector<sne::GameObject *>();
	glm::vec3 purple{0.5, 0.2, 0.6},
		bleu{0.2, 0.2, 0.8};

	glm::vec3 center{0, 10, 0};
	sne::GameObject *cube = createCube(_physicManager, center, purple);
	cube->setName("Cube purple");
	_physicManager.getLast()->setAcceleration({0, -1, 0});
	addGameObject(cube);

	glm::vec3 center2{0, 0, 0};

	for (int i = -10; i < 11; i++)
	{
		// above
		cube = createCube(_physicManager, center2 + glm::vec3{i, 0, 1}, bleu, true);
		addGameObject(cube);

		// middle
		cube = createCube(_physicManager, center2 + glm::vec3{i, 0, 0}, bleu, true);
		addGameObject(cube);

		// behind
		cube = createCube(_physicManager, center2 + glm::vec3{i, 0, -1}, bleu, true);
		addGameObject(cube);
	}
}

void PhysicScene2::unload()
{
	_physicManager.clear();
}

void PhysicScene2::update()
{
	sne::Scene::update();
	_physicManager.update();
}
