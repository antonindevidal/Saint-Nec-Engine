#include "GrassScene.hpp"



GrassScene::GrassScene() : Scene::Scene(), sunPos({ 1.0,0.0,0.0 })
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


	//Basic grass terrain
	/*
	{
		sne::GameObject* grassBlade = new sne::GameObject();
		grassBlade->setName("grass blade");
		addGameObject(grassBlade);
		grassBlade->addComponent(new GrassComponent(100, 100, 1000000, "resources/shaders/grassShader/grass.vert", "resources/shaders/grassShader/grass.frag"));
		grassBlade->translate({ 0.0f,0.0f,0.0f });
	}*/

	//Chunk terrain
	{
		sne::GameObject* grassBlade = new sne::GameObject();
		grassBlade->setName("grass blade");
		addGameObject(grassBlade);
		grassBlade->addComponent(new GrassChunkComponent(100, 10, 3000, "resources/shaders/grassShader/grass.vert", "resources/shaders/grassShader/grass.frag"));
		grassBlade->translate({ 0.0f,0.0f,0.0f });
	}

	sne::GameObject* plane = new sne::GameObject();
	plane->setName("plane");
	addGameObject(plane);
	sne::graphics::Plane* planeComp = new sne::graphics::Plane(100, 100, 1, "resources/shaders/color.vert", "resources/shaders/color.frag");
	planeComp->getShader().setVec3("color", { 0.0f, 0.30f, 0.02f });
	plane->addComponent(planeComp);
	plane->translate({ 50.0f,0.0f,50.0f });


	directionnalLight = glm::vec3(0.0f, 1.0f, 0.0f);

}

void GrassScene::unload()
{
	for (sne::GameObject* g : gameObjects)
	{
		delete g;
	}
}

void GrassScene::update()
{
	Scene::update();

	//directionnalLight = glm::vec3(cos(Time::getTimeSinceStart() *0.8f),0.0f , sin(Time::getTimeSinceStart() * 0.8f));
}

