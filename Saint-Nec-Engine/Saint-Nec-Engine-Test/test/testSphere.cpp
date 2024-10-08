// Entetes //---------------------------------------------------------------------------------------
#define _USE_MATH_DEFINES
#include <iostream>
#include <catch.hpp>
#include <cmath>
#include <physics/SphereCollider.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// Tests //-----------------------------------------------------------------------------------------
using namespace sne;
using namespace physics;

//--------------------------------------------------------------------------------------------------
TEST_CASE("TEST SPHERECOLLIDER CONSTRUCTORS")
{
    const SphereCollider sphere{glm::vec3{2, 2, 1}, 2.7589};

    CHECK(sphere.getRadius() == 2.7589f);
    CHECK(sphere.getCenter() == glm::vec3{2, 2, 1});
}