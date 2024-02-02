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
	void drawUI() override;
	void draw() const override;


private:

	float sunAngle;
	const sne::graphics::Shader* waterShader;

	struct Wave
	{
		float amplitude;
		float wavelenght;
		float speed;
		float steepness; //between 0 and 1
		float direction; //in radians
	};

	std::vector<Wave> waves;
	void setWavesValues() const;

};
