#pragma once
#include <architecture/Scene.hpp>
#include <graphics/Cube.hpp>
#include <graphics/Plane.hpp>
#include <graphics/TessellatedPlane.hpp>
#include <tracy/Tracy.hpp>


class TerrainScene: public sne::Scene
{
public:
	TerrainScene();

	void load() override;
	void unload() override;
};