#pragma once
#include <architecture/Scene.hpp>

class TerrainScene: public sne::Scene
{
	TerrainScene();

	void load() override;
	void unload() override;
};