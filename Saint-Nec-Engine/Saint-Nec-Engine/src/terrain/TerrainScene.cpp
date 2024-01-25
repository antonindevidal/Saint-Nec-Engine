#include "TerrainScene.hpp"

TerrainScene::TerrainScene(): Scene::Scene()
{
}

void TerrainScene::load()
{
	ZoneScopedN("TerrainSceneLoad");
	gameObjects = std::vector<sne::GameObject*>();


	//LOD TERRAIN
	{
		auto* terrainLOD = new sne::GameObject();
		terrainLOD->setName("TerrainLOD");
		addGameObject(terrainLOD);
		auto* planeLOD = new sne::graphics::TessellatedPlane(300, 300, 1, "resources/shaders/terrain/tessellation/tessellation.vert", "resources/shaders/terrain/tessellation/tessellation.frag", "resources/shaders/terrain/tessellation/tessellation.tesc", "resources/shaders/terrain/tessellation/tessellation.tese");
		glm::vec3 lightDir = glm::vec3(0.0f, 0.8f, 0.3f);

		planeLOD->addTexture("resources/textures/noise.jpg", "heightmap");
		planeLOD->addTexture("resources/textures/noise_normal.jpg", "heightmapNormal");
		planeLOD->addTexture("resources/textures/rock.jpg", "rockTex");
		planeLOD->addTexture("resources/textures/grass.jpg", "grassTex");
		terrainLOD->addComponent(planeLOD);

		planeLOD->getShader().setVec3("lightDir", lightDir);
		planeLOD->getShader().setInt("minTess", 1);
		planeLOD->getShader().setInt("maxTess", 12);
		planeLOD->getShader().setFloat("maxDist", 20);
		planeLOD->getShader().setFloat("textureScaling", 300.0f);

	}
	/*
	//NORMAL TERRAIN
	{
		sne::GameObject* terrain = new sne::GameObject();
		terrain->setName("Terrain");
		addGameObject(terrain);
		sne::graphics::Plane* plane = new sne::graphics::Plane(300, 300, 1, "resources/shaders/terrain/basic_terrain.vert", "resources/shaders/terrain/basic_terrain.frag");
		glm::vec3 lightDir = glm::vec3(0.0f, 0.8f, 0.3f);

		plane->addTexture("resources/textures/noise.jpg", "heightmap");
		plane->addTexture("resources/textures/noise_normal.jpg", "heightmapNormal");
		plane->addTexture("resources/textures/rock.jpg", "rockTex");
		plane->addTexture("resources/textures/grass.jpg", "grassTex");

		plane->getShader().setVec3("lightDir", lightDir);
		plane->getShader().setFloat("textureScaling", 300.0f);

		terrain->addComponent(plane);
	}
	*/



	//REFERENCE CUBE
	{
		sne::GameObject* cubeMonoColor = new sne::GameObject();
		addGameObject(cubeMonoColor);
		cubeMonoColor->setName("Monocolor cube");
		cubeMonoColor->addComponent(new sne::graphics::Cube("resources/shaders/color.vert", "resources/shaders/color.frag", glm::vec3{ 0.5,0.2,0.6 }));
		cubeMonoColor->translate(glm::vec3{ 0.0f, 0.0f, 0.0f });
	}

	
}

void TerrainScene::unload()
{
	for (sne::GameObject* g : gameObjects)
	{
		delete g;
	}
	gameObjects = std::vector<sne::GameObject*>();
}
