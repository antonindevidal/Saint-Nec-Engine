#include "GrassScene.hpp"
#include "../grass/GrassComponent.hpp"
#include "../grass/GrassChunkComponent.hpp"



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
		grassBlade->addComponent(new GrassComponent(400, 400, 30000000, "resources/shaders/grassShader/grass.vert", "resources/shaders/grassShader/grass.frag"));
		grassBlade->translate({ 0.0f,0.0f,0.0f });
		grassBlade->translate({ -200.0f,0.0f,-200.0f });
	}*/

	//Chunk terrain
	
	{
		sne::GameObject* grassBlade = new sne::GameObject();
		grassBlade->setName("grass blade");
		addGameObject(grassBlade);
		grassBlade->addComponent(new GrassChunkComponent(100, 10, 1000, "resources/shaders/grassShader/grass.vert", "resources/shaders/grassShader/grass.frag"));
		grassBlade->translate({ -50.0f,0.0f,-50.0f });
	}
	
	{
		sne::GameObject* sb = new sne::GameObject();
		sb->setName("Skybox");
		sb->addComponent(new sne::graphics::Skybox({ "resources/textures/skybox/nx.png","resources/textures/skybox/px.png","resources/textures/skybox/py.png","resources/textures/skybox/ny.png","resources/textures/skybox/nz.png","resources/textures/skybox/pz.png" }
													, "resources/shaders/skybox.vert", "resources/shaders/skybox.frag"));
		addGameObject(sb);
	}
	
	sne::GameObject* plane = new sne::GameObject();
	plane->setName("plane");
	addGameObject(plane);
	sne::graphics::Plane* planeComp = new sne::graphics::Plane(100, 100, 1, "resources/shaders/color.vert", "resources/shaders/color.frag");
	planeComp->getShader().setVec3("color", { 0.0f, 0.30f, 0.02f });
	plane->addComponent(planeComp);
	

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

