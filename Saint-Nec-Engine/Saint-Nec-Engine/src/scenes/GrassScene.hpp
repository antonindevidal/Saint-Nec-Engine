#pragma once 

#include <architecture/Scene.hpp>
#include <graphics/Cube.hpp>
#include <graphics/Plane.hpp>
#include <graphics/Skybox.hpp>
#include <imgui.h>
#include <glm/glm.hpp>


class GrassScene : public sne::Scene
{
public:
	GrassScene();

	void load() override;
	void unload() override;


	void update() override;

	void drawUI() override;


private:


	/**
	 * @brief Horizontal angle for the directionnal light (in radians).
	 */
	float sunAngle;

	/**
	 * Vertical orientation for the directionnal light.
	 */
	float sunOrbit;
};