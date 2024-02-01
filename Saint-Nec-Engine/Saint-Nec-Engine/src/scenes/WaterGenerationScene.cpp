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
		{0.5f, 5.0f, 1.0f, {std::cos(0), std::sin(0)}},
		//{1.0f, 8.5f, 1.5f, {std::cos(0), std::sin(0)}},
		//{2.0f, 4.0f, 1.2f, {std::cos(0), std::sin(0)}},
	};
	setWavesValues(p->getShader(), waves);
	p->getShader().setVec3("waterColor", { 0.21,0.26,0.63 });
	water->addComponent(p);
	
	
	gameObjects.push_back(water);


	// Multicolor cube example
	auto* cube = new sne::GameObject();
	cube->setName("Basic cube");
	addGameObject(cube);
	cube->addComponent(new sne::graphics::Cube("resources/shaders/basic.vert", "resources/shaders/basic.frag"));
	gameObjects.push_back(cube);
	directionnalLight = { std::cos(0), 0.0, std::sin( 0) };

}

void WaterGenerationScene::unload()
{
}

void WaterGenerationScene::update()
{
	sne::Scene::update();
	//directionnalLight = { std::cos(Time::getTimeSinceStart() * 0.8f), -1.0, std::sin(Time::getTimeSinceStart() * 0.8f) };
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
		shader.setVec2(uniformName + ".direction", wave.direction);
		i++;
	}
	shader.setInt("nWaves", i);
}
