#include "WaterGenerationScene.hpp"

WaterGenerationScene::WaterGenerationScene() : sne::Scene()
{
}

void WaterGenerationScene::load()
{
	gameObjects = std::vector<sne::GameObject*>();

	sne::GameObject* water = new sne::GameObject();
	sne::graphics::Plane* p = new sne::graphics::Plane(50, 50, 3, "resources/shaders/water/water.vert", "resources/shaders/water/water.frag");
	
	std::vector<Wave> waves = {
		{0.5f, 5.0f, 1.0f},
		{1.0f, 8.5f, 1.5f},
		{2.0f, 4.0f, 1.2f},
	};
	setWavesValues(p->getShader(), waves);

	water->addComponent(p);
	
	
	gameObjects.push_back(water);


	// Multicolor cube example
	auto* cube = new sne::GameObject();
	cube->setName("Basic cube");
	addGameObject(cube);
	cube->addComponent(new sne::graphics::Cube("resources/shaders/basic.vert", "resources/shaders/basic.frag"));
	gameObjects.push_back(cube);
}

void WaterGenerationScene::unload()
{
}

void WaterGenerationScene::update()
{
	sne::Scene::update();
}

void WaterGenerationScene::setWavesValues(const sne::graphics::Shader& shader, const std::vector<Wave>& waves)
{
	int i = 0;
	std::string uniformName;
	for (const auto& wave : waves)
	{
		uniformName = "waves[" + std::to_string(i) + "]";
		shader.setFloat(uniformName + ".amplitude", wave.amplitude);
		shader.setFloat(uniformName + ".wavelenght", wave.wavelenght);
		shader.setFloat(uniformName + ".speed", wave.speed);
		i++;
	}
	shader.setInt("nWaves", i);
}
