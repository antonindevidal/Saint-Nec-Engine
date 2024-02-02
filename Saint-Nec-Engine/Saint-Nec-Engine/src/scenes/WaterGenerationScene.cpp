#include "WaterGenerationScene.hpp"
#include <imgui.h>
WaterGenerationScene::WaterGenerationScene() : sne::Scene(), sunAngle(0.0f),waterShader(nullptr), waves()
{
}

void WaterGenerationScene::load()
{
	gameObjects = std::vector<sne::GameObject*>();

	sne::GameObject* water = new sne::GameObject();
	sne::graphics::Plane* p = new sne::graphics::Plane(400, 400, 3, "resources/shaders/water/water.vert", "resources/shaders/water/water.frag");
	
	waves = {
		{0.2f, 5.0f, 8.0f, 0.0f, glm::radians(45.0f)},
		{0.4f, 8.5f, 6.0f, 0.0f, glm::radians(-20.0f)},
		{0.8f, 4.0f, 3.0f, 0.0f, glm::radians(0.0f)},
		{0.6f, 7.0f, 5.0f, 0.0f, glm::radians(150.0f)},
		{0.1f, 3.0f, 9.0f, 0.0f, glm::radians(-105.0f)},
	};
	
	p->getShader().setVec3("waterColor", { 0.21,0.26,0.63 });
	water->addComponent(p);
	waterShader = &(p->getShader());
	setWavesValues();
	gameObjects.push_back(water);


	// Multicolor cube example
	auto* cube = new sne::GameObject();
	cube->setName("Basic cube");
	addGameObject(cube);
	cube->addComponent(new sne::graphics::Cube("resources/shaders/basic.vert", "resources/shaders/basic.frag"));
	gameObjects.push_back(cube);

	auto* skybox = new sne::GameObject();
	addGameObject(skybox);
	skybox->setName("skybox");
	skybox->addComponent(new sne::graphics::Skybox({ "resources/textures/skybox/nx.png","resources/textures/skybox/px.png","resources/textures/skybox/py.png","resources/textures/skybox/ny.png","resources/textures/skybox/nz.png","resources/textures/skybox/pz.png" }, "resources/shaders/skybox.vert", "resources/shaders/skybox.frag"));


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

	ImGui::SliderAngle("Sun direction", &sunAngle);
	int i = 0;
	for (Wave& w : waves)
	{
		if (ImGui::CollapsingHeader(("Wave " + i)))
		{
			ImGui::SliderFloat("Amplitude " + i, &(w.amplitude), 0.0f, 4.0f);
			ImGui::SliderFloat("Wavelength " + i, &(w.wavelenght), 0.0f, 20.0f);
			ImGui::SliderFloat("Speed " + i, &(w.speed), 0.0f, 20.0f);
			ImGui::SliderFloat("Steepness " + i, &(w.steepness), 0.0f, 1.0f);
			ImGui::SliderAngle("Direction " + i, &(w.direction));
			ImGui::Separator();
		}
		
		i++;
	}

	ImGui::End();
}
void WaterGenerationScene::draw() const
{
	Scene::draw();
	waterShader->use();
	setWavesValues();
	waterShader->setVec3("sunDir", directionnalLight);
}


void WaterGenerationScene::setWavesValues() const
{
	int i = 0;
	std::string uniformName;
	for (const auto& wave : waves)
	{
		uniformName = "waves[" + std::to_string(i) + "]";
		waterShader->setFloat(uniformName + ".amplitude", wave.amplitude);
		waterShader->setFloat(uniformName + ".wavelenght", wave.wavelenght);
		waterShader->setFloat(uniformName + ".speed", wave.speed);
		waterShader->setVec2(uniformName + ".direction", { std::cos(wave.direction), std::sin(wave.direction) });
		i++;
	}
	waterShader->setInt("nWaves", i);
}
