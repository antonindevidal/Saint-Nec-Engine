// Entetes //---------------------------------------------------------------------------------------
#include <iostream>
#include <catch.hpp>
#include <cmath>
#include <physics/SphereCollider.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <architecture/PhysicManager.hpp>

// Tests //-----------------------------------------------------------------------------------------
using namespace sne;
using namespace saintNecPhysics;

//--------------------------------------------------------------------------------------------------
TEST_CASE("TEST SPHERECOLLIDER CONSTRUCTORS")
{
    const SphereCollider sphere{glm::vec3{2, 2, 1}, 2.7589};

    CHECK(sphere.getRadius() == 2.7589);
    CHECK(sphere.getCenter() == glm::vec3{2, 2, 1});

    std::unique_ptr<sne::PhysicManager> &i = PhysicManager::getInstance();
}