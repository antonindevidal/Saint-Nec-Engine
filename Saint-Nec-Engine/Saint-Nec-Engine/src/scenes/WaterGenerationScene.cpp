#include "WaterGenerationScene.hpp"
#include <imgui.h>
WaterGenerationScene::WaterGenerationScene() : sne::Scene()
{
}

void WaterGenerationScene::load()
{
	gameObjects = std::vector<sne::GameObject*>();

	sne::GameObject* water = new sne::GameObject();
	sne::graphics::Plane* p = new sne::graphics::Plane(50, 50, 3, "resources/shaders/water/water.vert", "resources/shaders/water/water.frag");
	
	std::vector<Wave> waves = {
		{0.5f, 5.0f, 4.0f, {std::cos(3.14/4.0), std::sin(3.14/4.0)}},
		//{1.0f, 8.5f, 1.9f, {std::cos(1), std::sin(1)}},
		//{1.2f, 4.0f, 0.5f, {std::cos(-1), std::sin(-1)}},
	};
	setWavesValues(p->getShader(), waves);
	p->getShader().setVec3("waterColor", { 0.21,0.26,0.63 });
	water->addComponent(p);
	waterShader = &(p->getShader());
	
	gameObjects.push_back(water);


	// Multicolor cube example
	auto* cube = new sne::GameObject();
	cube->setName("Basic cube");
	addGameObject(cube);
	cube->addComponent(new sne::graphics::Cube("resources/shaders/basic.vert", "resources/shaders/basic.frag"));
	gameObjects.push_back(cube);
	directionnalLight = glm::normalize(glm::vec3(1,-1,1));

}

void WaterGenerationScene::unload()
{
}

void WaterGenerationScene::update()
{
	sne::Scene::update();
	directionnalLight = glm::normalize(glm::vec3(std::cos(sunAngle), -1, std::sin(sunAngle)));
}

void WaterGenerationScene::drawUI()
{
	sne::Scene::draw();

	ImGui::Begin("water");

	ImGui::SliderAngle("test", &sunAngle);

	ImGui::End();
}
void WaterGenerationScene::draw() const
{
	std::cout << sunAngle<< std::endl;
	waterShader->setVec3("sunDir", directionnalLight);
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
