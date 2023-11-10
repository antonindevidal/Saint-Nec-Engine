#pragma once
#include <architecture/Scene.hpp>
#include <graphics/Cube.hpp>
#include "components/TerrainComponent.hpp"


class TerrainScene: public sne::Scene
{
public:
	TerrainScene();

	void load() override;
	void unload() override;
};