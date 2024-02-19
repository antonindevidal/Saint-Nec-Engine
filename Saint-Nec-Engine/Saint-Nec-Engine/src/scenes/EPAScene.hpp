#pragma once

#include <architecture/Scene.hpp>
#include <architecture/GameObject.hpp>
#include <architecture/PhysicManager.hpp>
#include <graphics/Cube.hpp>
#include <physics/BoxCollider.hpp>
#include <physics/PhysicObject.hpp>

class EPAScene : public sne::Scene {

private:
	sne::PhysicManager _physicManager{};
public:

	EPAScene();

	void load() override;
	void unload() override;
	void update() override;
};