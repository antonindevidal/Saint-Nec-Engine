#include "FirstScene.hpp"



FirstScene::FirstScene(): Scene::Scene()
{

}

void FirstScene::load()
{
	gameObjects = std::vector<sne::GameObject*>();

	sne::GameObject* skybox = new sne::GameObject();
	addGameObject(skybox);
	skybox->setName("skybox");
	skybox->addComponent(new sne::graphics::Skybox({ "resources/textures/skybox/nx.png","resources/textures/skybox/px.png","resources/textures/skybox/py.png","resources/textures/skybox/ny.png","resources/textures/skybox/nz.png","resources/textures/skybox/pz.png" }, "resources/shaders/skybox.vert", "resources/shaders/skybox.frag"));


	// Multicolor cube example
	sne::GameObject* cube = new sne::GameObject();
	cube->setName("Basic cube");
	addGameObject(cube);
	cube->addComponent(new sne::graphics::Cube("resources/shaders/basic.vert", "resources/shaders/basic.frag"));



	// Monochrome cube example
	sne::GameObject* cubeMonoColor = new sne::GameObject();
	addGameObject(cubeMonoColor);
	cubeMonoColor->setName("Monocolor cube");
	cubeMonoColor->addComponent(new sne::graphics::Cube("resources/shaders/color.vert", "resources/shaders/color.frag", glm::vec3{ 0.5,0.2,0.6 }));
	cubeMonoColor->translate(glm::vec3{ -1.0f, 0.0f, 0.0f });


	// Textured cube example
	sne::GameObject* cubeTextured = new sne::GameObject();
	addGameObject(cubeTextured);
	cubeTextured->setName("Textured Cube");
	sne::graphics::Cube* cubeComponent = new sne::graphics::Cube("resources/shaders/basic.vert", "resources/shaders/texture.frag");
	cubeComponent->addTexture("resources/textures/elie2.jpg", "ourTexture");
	cubeTextured->addComponent(cubeComponent);
	cubeTextured->translate(glm::vec3{ 1.0f, 0.0f, 0.0f });

	}

void FirstScene::unload()
{
	for (sne::GameObject *g : gameObjects)
	{
		delete g;
	}
}
