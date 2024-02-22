#pragma once 

#include <architecture/Scene.hpp>
#include <graphics/Cube.hpp>
#include <graphics/Sphere.hpp>
#include <graphics/Skybox.hpp>


class FirstScene: public sne::Scene
{
public:
	FirstScene();

	void load() override;
	void unload() override;
};