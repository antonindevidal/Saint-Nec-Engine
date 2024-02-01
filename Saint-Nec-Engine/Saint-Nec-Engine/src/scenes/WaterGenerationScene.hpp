#pragma once 

#include <architecture/Scene.hpp>
#include <graphics/Cube.hpp>
#include <graphics/Plane.hpp>
#include <graphics/Skybox.hpp>
#include <graphics/Plane.hpp>
#include <graphics/Shader.hpp>


class WaterGenerationScene : public sne::Scene
{
public:
	WaterGenerationScene();

	void load() override;
	void unload() override;


	void update() override;


private:
	struct Wave
	{
		float amplitude;
		float wavelenght;
		float speed;
		glm::vec2 direction;
	};
	void setWavesValues(const sne::graphics::Shader& shader, const std::vector<Wave>& waves);

};
