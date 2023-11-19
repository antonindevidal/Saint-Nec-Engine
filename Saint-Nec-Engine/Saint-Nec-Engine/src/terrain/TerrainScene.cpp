#include "TerrainScene.hpp"
TerrainScene::TerrainScene(): Scene::Scene()
{
}

void TerrainScene::load()
{
	gameObjects = std::vector<sne::GameObject*>();

	/*
	sne::GameObject* terrain = new sne::GameObject();
	terrain->setName("Terrain");
	addGameObject(terrain);	
	sne::graphics::Plane* plane = new sne::graphics::Plane(300, 300, 5, "resources/shaders/terrain/basic_terrain.vert", "resources/shaders/terrain/basic_terrain.frag");
	plane->addTexture("resources/textures/noise.jpg","heightmap");
	terrain->addComponent(plane);
	*/
	sne::GameObject* terrainLOD = new sne::GameObject();
	terrainLOD->setName("Terrain");
	addGameObject(terrainLOD);
	TessellationTerrain* planeLOD = new TessellationTerrain(300, 300, 1, "resources/shaders/terrain/tessellation/tessellation.vert", "resources/shaders/terrain/tessellation/tessellation.frag", "resources/shaders/terrain/tessellation/tessellation.tesc", "resources/shaders/terrain/tessellation/tessellation.tese");
	planeLOD->addTexture("resources/textures/noise.jpg", "heightmap");
	terrainLOD->addComponent(planeLOD);
	//sne::graphics::Plane* p = new  sne::graphics::Plane(10, 10, 1, "resources/shaders/terrain/basic_terrain.vert", "resources/shaders/terrain/basic_terrain.frag");
	//p->addTexture("resources/textures/noise.jpg", "heightmap");
	//terrainLOD->addComponent(p);


	sne::GameObject* cubeMonoColor = new sne::GameObject();
	addGameObject(cubeMonoColor);
	cubeMonoColor->setName("Monocolor cube");
	cubeMonoColor->addComponent(new sne::graphics::Cube("resources/shaders/color.vert", "resources/shaders/color.frag", glm::vec3{ 0.5,0.2,0.6 }));
	cubeMonoColor->translate(glm::vec3{ 0.0f, 0.0f, 0.0f });
	
	
}

void TerrainScene::unload()
{
	for (sne::GameObject* g : gameObjects)
	{
		delete g;
	}
	gameObjects = std::vector<sne::GameObject*>();
}
