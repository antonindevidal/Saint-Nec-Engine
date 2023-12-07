#include "GrassScene.hpp"



GrassScene::GrassScene() : Scene::Scene()
{

}

void GrassScene::load()
{
	gameObjects = std::vector<sne::GameObject*>();
	// Multicolor cube example
	sne::GameObject* cube = new sne::GameObject();
	cube->setName("Basic cube");
	addGameObject(cube);
	cube->addComponent(new sne::graphics::Cube("resources/shaders/basic.vert", "resources/shaders/basic.frag"));


	sne::GameObject* grassBlade = new sne::GameObject();
	grassBlade->setName("grass blade");
	addGameObject(grassBlade);
	grassBlade->addComponent(new GrassComponent("resources/shaders/grassShader/grass.vert", "resources/shaders/grassShader/grass.frag"));
	grassBlade->translate({ 0.0f,1.0f,0.0f });


	sne::GameObject* plane = new sne::GameObject();
	plane->setName("plane");
	addGameObject(plane);
	sne::graphics::Plane* planeComp = new sne::graphics::Plane(10, 10, 1, "resources/shaders/color.vert", "resources/shaders/terrain/color.frag");
	plane->addComponent(planeComp);

}

void GrassScene::unload()
{
	for (sne::GameObject* g : gameObjects)
	{
		delete g;
	}
}
