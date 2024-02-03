#pragma once 

#include <cstdlib>
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
	float ambientLight;
	int specularExp;
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
	void generateWaves(int nWaves, float medianWavelength, float medianAmplitude, float medianSteepness);

	/**
	 * @brief Generate n waves with Fractional Brownian motion.
	 * 
	 * @param nWaves Number of waves
	 * @param initialWavelegth
	 * @param initialAmplitude
	 * @param wavelengthFactor Must be > 1.0
	 * @param amplitudeFactor Must be < 1.0
	 */
	void generateWaves(int nWaves, float initialWavelegth, float initialAmplitude, float wavelengthFactor, float amplitudeFactor);

	
	void setWavesValues() const;

};
