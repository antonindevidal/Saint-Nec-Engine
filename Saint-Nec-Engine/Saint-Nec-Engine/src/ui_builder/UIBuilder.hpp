#pragma once

#include <architecture/GameObject.hpp>
#include <architecture/PhysicManager.hpp>
#include <graphics/Cube.hpp>
#include <physics/BoxCollider.hpp>
#include <physics/PhysicObject.hpp>
#include <architecture/PhysicManager.hpp>

sne::GameObject *createCube(sne::PhysicManager &_physicManager, const glm::vec3 &center, const glm::vec3 &color, bool fixe = false, float size = 1.0f);
sne::GameObject *createBox(sne::PhysicManager &_physicManager, const glm::vec3 &center, const glm::vec3 &color,
                           float w, float h, float d, bool fixe = false);