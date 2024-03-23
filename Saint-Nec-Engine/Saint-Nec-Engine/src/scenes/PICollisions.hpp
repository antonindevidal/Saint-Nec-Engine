#pragma once

#include <architecture/Scene.hpp>
#include <architecture/GameObject.hpp>
#include <architecture/PhysicManager.hpp>
#include <memory>
#include <graphics/Cube.hpp>
#include <physics/BoxCollider.hpp>
#include <physics/PhysicObject.hpp>
#include <architecture/Time.hpp>

class PICollisions : public sne::Scene {

private:
	sne::PhysicManager _physicManager{};
public:

	float lastUpdate = 0;
	int counter = 0;
	PICollisions();

	void load() override;
	void unload() override;
	void update() override;
};