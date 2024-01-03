#pragma once

#include <architecture/Scene.hpp>
#include <architecture/GameObject.hpp>
#include <architecture/PhysicManager.hpp>
#include <memory>
#include <graphics/Cube.hpp>
#include <physics/BoxCollider.hpp>
#include <physics/PhysicObject.hpp>


class PhysicScene : public sne::Scene {

private:
	std::unique_ptr<sne::PhysicManager> &_physicManager = sne::PhysicManager::getInstance();

public:

	PhysicScene();

	void load() override;
	void unload() override;
	void update() override;
};