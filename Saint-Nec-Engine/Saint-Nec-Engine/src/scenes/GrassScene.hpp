#pragma once 

#include <architecture/Scene.hpp>
#include <graphics/Cube.hpp>
#include <graphics/Plane.hpp>
#include <graphics/Skybox.hpp>


class GrassScene : public sne::Scene
{
public:
	GrassScene();

	void load() override;
	void unload() override;


	void update() override;


private:

	glm::vec3 sunPos;
};