#pragma once
/**
 * @file algorithms.hpp
 * @brief algorithm for collision detection.
 * @author Abdeljalil ZOGHLAMI, Antonin DEVIDAL.
 * @date november 17th 2023.
 *
 */


#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <architecture/util.hpp>
#include <algorithm>
#include "util.hpp"
#include "BoxCollider.hpp"
#include "SphereCollider.hpp"
#include <utility>
#include "PhysicObject.hpp"


namespace sne::saintNecPhysics
{
    std::vector<std::pair<PhysicObject*, PhysicObject*>> sweepAndPrune(std::vector<PhysicObject*>&);
}
