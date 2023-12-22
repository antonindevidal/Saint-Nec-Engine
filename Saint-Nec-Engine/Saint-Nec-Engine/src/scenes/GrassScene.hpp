#pragma once 

#include <architecture/Scene.hpp>
#include <graphics/Cube.hpp>
#include <graphics/Plane.hpp>

#include "../grass/GrassComponent.hpp"
#include "../grass/GrassChunkComponent.hpp"

class GrassScene : public sne::Scene
{
public:
	GrassScene();

	void load() override;
	void unload() override;
};