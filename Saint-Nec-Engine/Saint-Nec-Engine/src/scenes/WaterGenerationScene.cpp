#include "WaterGenerationScene.hpp"
#include <imgui.h>
WaterGenerationScene::WaterGenerationScene() : sne::Scene(), sunAngle(0.0f),sunOrbit(-1.0f), ambientLight(0.8f), specularExp(2),useSpecular(true), waterColor(50 / 255.0f, 82 / 255.0f, 107 / 255.0f), waterShader(nullptr), waves()
{
}

void WaterGenerationScene::load()
{
	gameObjects = std::vector<sne::GameObject*>();

	sne::GameObject* water = new sne::GameObject();
	sne::graphics::Plane* p = new sne::graphics::Plane(400, 400, 5, "resources/shaders/water/water.vert", "resources/shaders/water/water.frag");

	generateWaves(10, 8, 0.4f, 1.3f, 0.92f);
	
	p->getShader().setVec3("waterColor", waterColor);
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


	directionnalLight = glm::normalize(glm::vec3(0,-1,0));

}



void WaterGenerationScene::unload()
{
	Scene::unload();
}

void WaterGenerationScene::update()
{
	sne::Scene::update();
	directionnalLight = glm::normalize(glm::vec3(std::cos(sunAngle), sunOrbit, std::sin(sunAngle)));
}

void WaterGenerationScene::drawUI()
{
	sne::Scene::draw();

	ImGui::Begin("water");

	ImGui::SliderAngle("Sun direction", &sunAngle);
	ImGui::SliderFloat("Sun orbit", &sunOrbit,-1.0f,1.0f);
	ImGui::SliderInt("Specular exp", &specularExp,1,50);
	ImGui::SliderFloat("Ambient Light", &ambientLight,0.0f,1.0f);
	ImGui::Checkbox("Use Specular", &useSpecular);
	ImGui::ColorPicker3("Water Color", &waterColor[0]);
	ImGui::Separator();
	int i = 0;
	
	for (Wave& w : waves)
	{
		std::string id = "##" + i;
		if (ImGui::CollapsingHeader(("Wave " +std::to_string(i)).c_str()))
		{
			
			ImGui::SliderFloat(("Amplitude"+i+id).c_str(), &(w.amplitude), 0.01f, 4.0f);
			ImGui::SliderFloat(("Wavelength" + i +id).c_str(), &(w.wavelenght), 0.0f, 20.0f);
			ImGui::SliderFloat(("Speed" + i + id).c_str(), &(w.speed), 0.0f, 20.0f);
			ImGui::SliderFloat(("Steepness" + i + id).c_str(), &(w.steepness), 0.0f, 1.0f);
			ImGui::SliderAngle(("Direction" + i + id).c_str(), &(w.direction));
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
	waterShader->setInt("specularExp", specularExp);
	waterShader->setFloat("ambient", ambientLight);
	waterShader->setVec3("cameraDir", sne::SceneManager::getInstance()->getCurrentScene()->getCamera().getFront());
	waterShader->setVec3("waterColor", waterColor);
	waterShader->setInt("useSpecular", useSpecular);
}

void WaterGenerationScene::generateWaves(int nWaves, float initialWavelegth, float initialAmplitude, float wavelengthFactor, float amplitudeFactor)
{
	float lastWL = initialWavelegth, lastAmp = initialAmplitude;
	for (int i = 0; i < nWaves; i++)
	{
		waves.push_back(
			{
				lastAmp,
				lastWL,
				lastWL * .2f + (std::rand() % 10) / 10.0f,//lastWL * initialAmplitude/ initialWavelegth,
				1.0f,
				(std::rand() % 618) / 100.0f
			}
		);
		lastWL = lastWL * wavelengthFactor;
		lastAmp = lastAmp * amplitudeFactor;
	}
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
		waterShader->setFloat(uniformName + ".steepness", wave.steepness);
		waterShader->setVec2(uniformName + ".direction", { std::cos(wave.direction), std::sin(wave.direction) });
		i++;
	}
	waterShader->setInt("nWaves", i);
}
