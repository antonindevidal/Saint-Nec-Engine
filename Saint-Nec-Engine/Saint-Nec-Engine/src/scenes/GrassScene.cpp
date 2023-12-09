#include "GrassScene.hpp"



GrassScene::GrassScene() : Scene::Scene()
{

}

void GrassScene::load()
{
	gameObjects = std::vector<sne::GameObject*>();

	// Multicolor cube example
	/*
	sne::GameObject* cube = new sne::GameObject();
	cube->setName("Basic cube");
	addGameObject(cube);
	cube->addComponent(new sne::graphics::Cube("resources/shaders/basic.vert", "resources/shaders/basic.frag"));
	*/

	sne::GameObject* grassBlade = new sne::GameObject();
	grassBlade->setName("grass blade");
	addGameObject(grassBlade);
	grassBlade->addComponent(new GrassComponent(5,5,200,"resources/shaders/grassShader/grass.vert", "resources/shaders/grassShader/grass.frag"));
	grassBlade->translate({ 0.0f,0.0f,0.0f });


	sne::GameObject* plane = new sne::GameObject();
	plane->setName("plane");
	addGameObject(plane);
	sne::graphics::Plane* planeComp = new sne::graphics::Plane(5, 5, 1, "resources/shaders/color.vert", "resources/shaders/color.frag");
	planeComp->getShader().setVec3("color",{ 0.9f, 0.9f, 0.9f });
	plane->addComponent(planeComp);
	plane->translate({ 2.5f,0.0f,2.5f });
	
}

void GrassScene::unload()
{
	for (sne::GameObject* g : gameObjects)
	{
		delete g;
	}
}
