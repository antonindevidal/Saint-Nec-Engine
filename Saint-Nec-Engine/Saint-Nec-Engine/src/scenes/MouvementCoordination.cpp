#include "MouvementCoordination.hpp"
#include "../ui_builder/UIBuilder.hpp"
#include "../Colors.hpp"


MouvementCoordination::MouvementCoordination()
{
}

void MouvementCoordination::load()
{
	gameObjects = std::vector<sne::GameObject*>();
	glm::vec3 center{ 2, 2, 2 };
	sne::GameObject* cube = createCube(_physicManager, center, purple, true);

	cube->rotate(45, { 1,1,1 });
	_physicManager.getLast()->setRotation({0, 3.14159 / 4, 0});
	addGameObject(cube);


	// draw axis to see rotation:
	for (int i = 0; i < 10; i++)
	{
		// x axis
		center = { i, 0, 0 };
		cube = createCube(_physicManager, center, blue, true);
		addGameObject(cube);

		// y axis
		center = { 0, i, 0 };
		cube = createCube(_physicManager, center, blue, true);
		addGameObject(cube);

		// z axis
		center = { 0, 0, i };
		cube = createCube(_physicManager, center, blue, true);
		addGameObject(cube);
	}

}

void MouvementCoordination::unload()
{
	_physicManager.clear();
}

void MouvementCoordination::update()
{
	sne::Scene::update();
	_physicManager.update();
}
