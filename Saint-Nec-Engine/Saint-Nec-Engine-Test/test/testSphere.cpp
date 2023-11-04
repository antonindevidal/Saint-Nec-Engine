// Entetes //---------------------------------------------------------------------------------------
#include <iostream>
#include <catch.hpp>
#include <cmath>
#include <architecture/Component.hpp>
#include <physics/SphereCollider.hpp>
#include <physics/SAT.hpp>

// Tests //-----------------------------------------------------------------------------------------
using namespace saintNecEngine;
using namespace saintNecPhysics;

//--------------------------------------------------------------------------------------------------
TEST_CASE("TEST SPHERECOLLIDER CONSTRUCTORS")
{
    const SphereCollider sphere{Vector3{2, 2, 1}, 2.7589};

    CHECK(sphere.getRadius() == 2.7589);
    CHECK(sphere.getCenter() == Vector3{2, 2, 1});
}