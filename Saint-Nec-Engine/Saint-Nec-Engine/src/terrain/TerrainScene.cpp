#include "TerrainScene.hpp"

TerrainScene::TerrainScene(): Scene::Scene()
{
}

void TerrainScene::load()
{
	gameObjects = std::vector<sne::GameObject*>();

	// Multicolor cube example
	sne::GameObject* terrain = new sne::GameObject();
	terrain->setName("Terrain");
	addGameObject(terrain);
	terrain->addComponent(new TerrainComponent("resources/textures/heightmap_puy_de_dome.jpg","resources/shaders/terrain/basic_terrain.vert", "resources/shaders/terrain/basic_terrain.frag", 20, 20, 5));

	
	sne::GameObject* cubeMonoColor = new sne::GameObject();
	addGameObject(cubeMonoColor);
	cubeMonoColor->setName("Monocolor cube");
	cubeMonoColor->addComponent(new sne::graphics::Cube("resources/shaders/color.vert", "resources/shaders/color.frag", glm::vec3{ 0.5,0.2,0.6 }));
	cubeMonoColor->translate(glm::vec3{ 0.0f, 0.0f, 0.0f });
	
}

void TerrainScene::unload()
{
}
