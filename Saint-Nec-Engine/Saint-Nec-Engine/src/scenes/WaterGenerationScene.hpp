#pragma once 
/**
 * @file WaterGenerationScene.hpp
 * @brief Scene to create Water Generation.
 * @author Antonin DEVIDAL
 * @date February 09th 2023
 *
 */
#include <cstdlib>
#include <architecture/Scene.hpp>
#include <graphics/Cube.hpp>
#include <graphics/Plane.hpp>
#include <graphics/Skybox.hpp>
#include <graphics/Plane.hpp>
#include <graphics/Shader.hpp>


 /**
* @class GraphicComponent
* @brief Scene to create Water Generation.
*/
class WaterGenerationScene : public sne::Scene
{
public:
	/**
	 * @brief Constructor for the scene.
	 */
	WaterGenerationScene();

	/**
	 * @brief Load the Scene.
	 */
	void load() override;

	/**
	 * @brief Unload the scene.
	 */
	void unload() override;

	/**
	 * @brief Where all the logic happens.
	 */
	void update() override;

	/**
	 * @brief Method to do all ImGUI calls.
	 */
	void drawUI() override;

	/**
	 * @brief geometry.
	 */
	void draw() const override;


private:

	/**
	 * @brief Horizontal angle for the directionnal light (in radians).
	 */
	float sunAngle;

	/**
	 * Vertical orientation for the directionnal light.
	 */
	float sunOrbit;

	/**
	 * @brief light value (between 0 and 1).
	 */
	float ambientLight;

	/**
	 * @brief Exponnential value for Blinn-Phong lighting.
	 */
	int specularExp;

	/**
	 * @brief Water color.
	 */
	glm::vec3 waterColor;

	/**
	 * @brief Pointer to the water's shader.
	 */
	const sne::graphics::Shader* waterShader;

	/**
	 * @brief Structure to store wave values sent to the shader.
	 */
	struct Wave
	{
		float amplitude;
		float wavelenght;
		float speed;
		float steepness; //between 0 and 1
		float direction; //in radians
	};

	/**
	 * @brief of waves.
	 */
	std::vector<Wave> waves;

	/**
	 * @brief Generate n waves.
	 * 
	 * @param nWaves Number of waves
	 * @param initialWavelegth
	 * @param initialAmplitude
	 * @param wavelengthFactor Must be > 1.0
	 * @param amplitudeFactor Must be < 1.0
	 */
	void generateWaves(int nWaves, float initialWavelegth, float initialAmplitude, float wavelengthFactor, float amplitudeFactor);

	/**
	 * Send waves values to the water shader.
	 */
	void setWavesValues() const;
};
