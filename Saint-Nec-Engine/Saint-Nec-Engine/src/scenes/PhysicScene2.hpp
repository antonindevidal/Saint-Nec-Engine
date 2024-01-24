#pragma once

#include <architecture/Scene.hpp>
#include <architecture/GameObject.hpp>
#include <architecture/PhysicManager.hpp>
#include <memory>
#include <graphics/Cube.hpp>
#include <physics/BoxCollider.hpp>
#include <physics/PhysicObject.hpp>

class PhysicScene2 : public sne::Scene {

private:
	sne::PhysicManager _physicManager{};
public:

	PhysicScene2();

	void load() override;
	void unload() override;
	void update() override;
};