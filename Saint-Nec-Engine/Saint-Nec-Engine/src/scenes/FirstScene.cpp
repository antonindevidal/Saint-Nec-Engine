#include "FirstScene.hpp"



FirstScene::FirstScene(): Scene::Scene()
{

}

void FirstScene::load()
{
	gameObjects = std::vector<sne::GameObject*>();

	auto* skybox = new sne::GameObject();
	addGameObject(skybox);
	skybox->setName("skybox");
	skybox->addComponent(new sne::graphics::Skybox({ "resources/textures/skybox/nx.png","resources/textures/skybox/px.png","resources/textures/skybox/py.png","resources/textures/skybox/ny.png","resources/textures/skybox/nz.png","resources/textures/skybox/pz.png" }, "resources/shaders/skybox.vert", "resources/shaders/skybox.frag"));

	/*
	// Multicolor cube example
	auto* cube = new sne::GameObject();
	cube->setName("Basic cube");
	addGameObject(cube);
	cube->addComponent(new sne::graphics::Cube("resources/shaders/basic.vert", "resources/shaders/basic.frag"));
	*/


	// Monochrome cube example
	auto* cubeMonoColor = new sne::GameObject();
	addGameObject(cubeMonoColor);
	cubeMonoColor->setName("Monocolor cube");
	cubeMonoColor->addComponent(new sne::graphics::Cube("resources/shaders/color.vert", "resources/shaders/color.frag", glm::vec3{ 0.5,0.2,0.6 }));
	cubeMonoColor->translate(glm::vec3{ -1.0f, 0.0f, 0.0f });


	// Textured cube example
	auto* cubeTextured = new sne::GameObject();
	addGameObject(cubeTextured);
	cubeTextured->setName("Textured Cube");
	auto* cubeComponent = new sne::graphics::Cube("resources/shaders/basic.vert", "resources/shaders/texture.frag");
	cubeComponent->addTexture("resources/textures/elie2.jpg", "ourTexture");
	cubeTextured->addComponent(cubeComponent);
	cubeTextured->translate(glm::vec3{ 1.0f, 0.0f, 0.0f });

	auto* sphere = new sne::GameObject();
	addGameObject(sphere);
	sphere->setName("Sphere");
	auto* sphereComponent = new sne::graphics::Sphere("resources/shaders/sphere.vert", "resources/shaders/sphere.frag");
	sphereComponent->getShader().setVec3("color", { 1.0,1.0,0.0 });
	sphere->addComponent(sphereComponent);

}

void FirstScene::unload()
{
	for (sne::GameObject *g : gameObjects)
	{
		delete g;
	}
}
