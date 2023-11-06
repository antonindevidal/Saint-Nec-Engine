#include "Game.hpp"

Game::Game(): sceneManager(sne::SceneManager::getInstance())
{
	sne::Scene* scene = new sne::Scene("Scene1");

	sceneManager->addScene(scene);
	sceneManager->changeScene(scene->getName());

	
	// Multicolor cube example
	sne::GameObject* cube = new sne::GameObject();
	cube->setName("Basic cube");
	scene->addGameObject(cube);
	cube->addComponent(new sne::graphics::Cube("resources/shaders/basic.vert", "resources/shaders/basic.frag"));
	

	
	// Monochrome cube example
	sne::GameObject* cubeMonoColor = new sne::GameObject();
	scene->addGameObject(cubeMonoColor);
	cubeMonoColor->setName("Monocolor cube");
	cubeMonoColor->addComponent(new sne::graphics::Cube("resources/shaders/color.vert", "resources/shaders/color.frag", glm::vec3{ 0.5,0.2,0.6 }));
	cubeMonoColor->translate(glm::vec3{ -1.0f, 0.0f, 0.0f });

	
	// Textured cube example
	sne::GameObject* cubeTextured = new sne::GameObject();
	scene->addGameObject(cubeTextured);
	cubeTextured->setName("Textured Cube");
	cubeTextured->addComponent(new sne::graphics::Cube("resources/shaders/basic.vert", "resources/shaders/texture.frag", "resources/textures/elie2.jpg"));
	cubeTextured->translate(glm::vec3{ 1.0f, 0.0f, 0.0f });
}

Game::~Game()
{
}

void Game::update()
{
	sceneManager->update();
}

void Game::draw() const
{
	sceneManager->draw();

	UiHelper::WindowSceneTree(sne::SceneManager::getInstance()->getCurrentScene());
}
