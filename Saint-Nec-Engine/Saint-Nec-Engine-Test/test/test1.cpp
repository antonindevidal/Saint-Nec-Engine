// Entetes //---------------------------------------------------------------------------------------
#include <iostream>
#include <catch.hpp>
#include <cmath>
#include <architecture/Component.hpp>
#include <physics/BoxCollider.hpp>
#include <physics/SphereCollider.hpp>
#include <physics/SAT.hpp>

// Tests //-----------------------------------------------------------------------------------------
using namespace saintNecEngine;
using namespace saintNecPhysics;

//------------------------------------------------------------------------------------------------ 1
TEST_CASE("TEST BOXCOLLIDER CONSTRUCTORS")
{
    const BoxCollider cube1{Vector3{2, 2, 1}, 2, 2, 2};
    std::vector<Vector3> cube1_points_list = {
        Vector3{1, 1, 0},
        Vector3{1, 1, 2},
        Vector3{1, 3, 0},
        Vector3{1, 3, 2},
        Vector3{3, 1, 0},
        Vector3{3, 1, 2},
        Vector3{3, 3, 0},
        Vector3{3, 3, 2}};

    CHECK(cube1.hasPoint(cube1_points_list[0]) == true);
    CHECK(cube1.hasPoint(cube1_points_list[1]) == true);
    CHECK(cube1.hasPoint(cube1_points_list[2]) == true);
    CHECK(cube1.hasPoint(cube1_points_list[3]) == true);
    CHECK(cube1.hasPoint(cube1_points_list[4]) == true);
    CHECK(cube1.hasPoint(cube1_points_list[5]) == true);
    CHECK(cube1.hasPoint(cube1_points_list[6]) == true);
    CHECK(cube1.hasPoint(cube1_points_list[7]) == true);
}

//------------------------------------------------------------------------------------------------ 2
TEST_CASE("TEST BASIC COLLISION WITHOUT ROTATION")
{
    using namespace saintNecEngine;
    using namespace saintNecPhysics;

    // Must collide
    const BoxCollider b1{
        Vector3{2, 2, 1}, 2, 2, 2};

    const BoxCollider b2{
        Vector3{3, 3, 1}, 2, 2, 2};

    const BoxCollider b3{
        Vector3{30, 30, 10}, 2, 2, 2};

    CHECK(hasSATCollision(b1, b2) == true);
    CHECK(hasSATCollision(b1, b3) == false);
    CHECK(hasSATCollision(b2, b3) == false);
}



TEST_CASE("TEST NORM")
{
    using namespace saintNecEngine;
    using namespace saintNecPhysics;

    Vector3 v1 = {0, 0, 0};
    Vector3 v2 = {1, 0, 0};
    Vector3 v3 = {3, 4, 0};

    CHECK(norm(v1) == Approx(0.0));
    CHECK(norm(v2) == Approx(1.0));   
    CHECK(norm(v3) == Approx(5.0));
}