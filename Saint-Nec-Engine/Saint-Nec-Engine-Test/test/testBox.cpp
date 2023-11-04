// Entetes //---------------------------------------------------------------------------------------
#include <iostream>
#include <catch.hpp>
#include <cmath>
#include <architecture/Component.hpp>
#include <physics/BoxCollider.hpp>
#include <physics/SAT.hpp>

// Tests //-----------------------------------------------------------------------------------------
using namespace sne;
using namespace saintNecPhysics;

//--------------------------------------------------------------------------------------------------
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

TEST_CASE("TEST ROTATION 1 - center origin")
{

    BoxCollider cube{
        Vector3{0, 0, 0}, 2, 2, 2};

    std::vector<Vector3> cube_points_before_rotation = {
        Vector3{-1, -1, -1},
        Vector3{-1, -1, 1},
        Vector3{-1, 1, -1},
        Vector3{-1, 1, 1},
        Vector3{1, -1, -1},
        Vector3{1, -1, 1},
        Vector3{1, 1, -1},
        Vector3{1, 1, 1}};

    CHECK(cube.hasPoint(cube_points_before_rotation[0]) == true);
    CHECK(cube.hasPoint(cube_points_before_rotation[1]) == true);
    CHECK(cube.hasPoint(cube_points_before_rotation[2]) == true);
    CHECK(cube.hasPoint(cube_points_before_rotation[3]) == true);
    CHECK(cube.hasPoint(cube_points_before_rotation[4]) == true);
    CHECK(cube.hasPoint(cube_points_before_rotation[5]) == true);
    CHECK(cube.hasPoint(cube_points_before_rotation[6]) == true);
    CHECK(cube.hasPoint(cube_points_before_rotation[7]) == true);

    cube.setRotation({0, 0, 0});
    std::vector<Vector3> cube_points_after_rotation = cube_points_before_rotation;

    CHECK(cube.contains(cube_points_after_rotation[0]) == true);
    CHECK(cube.contains(cube_points_after_rotation[1]) == true);
    CHECK(cube.contains(cube_points_after_rotation[2]) == true);
    CHECK(cube.contains(cube_points_after_rotation[3]) == true);
    CHECK(cube.contains(cube_points_after_rotation[4]) == true);
    CHECK(cube.contains(cube_points_after_rotation[5]) == true);
    CHECK(cube.contains(cube_points_after_rotation[6]) == true);
    CHECK(cube.contains(cube_points_after_rotation[7]) == true);

    cube.setRotation({0, M_PI / 2, 0});

    CHECK(cube.contains(cube_points_after_rotation[0]) == true);
    CHECK(cube.contains(cube_points_after_rotation[1]) == true);
    CHECK(cube.contains(cube_points_after_rotation[2]) == true);
    CHECK(cube.contains(cube_points_after_rotation[3]) == true);
    CHECK(cube.contains(cube_points_after_rotation[4]) == true);
    CHECK(cube.contains(cube_points_after_rotation[5]) == true);
    CHECK(cube.contains(cube_points_after_rotation[6]) == true);
    CHECK(cube.contains(cube_points_after_rotation[7]) == true);

    cube.setRotation({0, 0, M_PI / 2});

    CHECK(cube.contains(cube_points_after_rotation[0]) == true);
    CHECK(cube.contains(cube_points_after_rotation[1]) == true);
    CHECK(cube.contains(cube_points_after_rotation[2]) == true);
    CHECK(cube.contains(cube_points_after_rotation[3]) == true);
    CHECK(cube.contains(cube_points_after_rotation[4]) == true);
    CHECK(cube.contains(cube_points_after_rotation[5]) == true);
    CHECK(cube.contains(cube_points_after_rotation[6]) == true);
    CHECK(cube.contains(cube_points_after_rotation[7]) == true);

    cube.setRotation({0, M_PI / 4, 0});

    cube_points_after_rotation = {
        Vector3{-1.41421, -1, 0},
        Vector3{1.41421, -1, 0},
        Vector3{0, -1, -1.41421},
        Vector3{0, -1, 1.41421},
        Vector3{-1.41421, 1, 0},
        Vector3{1.41421, 1, 0},
        Vector3{0, 1, -1.41421},
        Vector3{0, 1, 1.41421}};
    CHECK(cube.contains(cube_points_after_rotation[0]) == true);
    CHECK(cube.contains(cube_points_after_rotation[1]) == true);
    CHECK(cube.contains(cube_points_after_rotation[2]) == true);
    CHECK(cube.contains(cube_points_after_rotation[3]) == true);
    CHECK(cube.contains(cube_points_after_rotation[4]) == true);
    CHECK(cube.contains(cube_points_after_rotation[5]) == true);
    CHECK(cube.contains(cube_points_after_rotation[6]) == true);
    CHECK(cube.contains(cube_points_after_rotation[7]) == true);
}

TEST_CASE("TEST ROTATION 2 - center any")
{

    BoxCollider cube{
        Vector3{1, 1, 1}, 2, 2, 2};

    std::vector<Vector3> cube_points_before_rotation = {
        Vector3{0, 0, 0},
        Vector3{0, 0, 2},
        Vector3{0, 2, 0},
        Vector3{0, 2, 2},
        Vector3{2, 0, 0},
        Vector3{2, 0, 2},
        Vector3{2, 2, 0},
        Vector3{2, 2, 2}};

    CHECK(cube.hasPoint(cube_points_before_rotation[0]) == true);
    CHECK(cube.hasPoint(cube_points_before_rotation[1]) == true);
    CHECK(cube.hasPoint(cube_points_before_rotation[2]) == true);
    CHECK(cube.hasPoint(cube_points_before_rotation[3]) == true);
    CHECK(cube.hasPoint(cube_points_before_rotation[4]) == true);
    CHECK(cube.hasPoint(cube_points_before_rotation[5]) == true);
    CHECK(cube.hasPoint(cube_points_before_rotation[6]) == true);
    CHECK(cube.hasPoint(cube_points_before_rotation[7]) == true);

    cube.setRotation({M_PI, 0, 0});
    std::vector<Vector3> cube_points_after_rotation = cube_points_before_rotation;

    CHECK(cube.contains(cube_points_after_rotation[0]) == true);
    CHECK(cube.contains(cube_points_after_rotation[1]) == true);
    CHECK(cube.contains(cube_points_after_rotation[2]) == true);
    CHECK(cube.contains(cube_points_after_rotation[3]) == true);
    CHECK(cube.contains(cube_points_after_rotation[4]) == true);
    CHECK(cube.contains(cube_points_after_rotation[5]) == true);
    CHECK(cube.contains(cube_points_after_rotation[6]) == true);
    CHECK(cube.contains(cube_points_after_rotation[7]) == true);

    cube.setRotation({0, M_PI, 0});

    CHECK(cube.contains(cube_points_after_rotation[0]) == true);
    CHECK(cube.contains(cube_points_after_rotation[1]) == true);
    CHECK(cube.contains(cube_points_after_rotation[2]) == true);
    CHECK(cube.contains(cube_points_after_rotation[3]) == true);
    CHECK(cube.contains(cube_points_after_rotation[4]) == true);
    CHECK(cube.contains(cube_points_after_rotation[5]) == true);
    CHECK(cube.contains(cube_points_after_rotation[6]) == true);
    CHECK(cube.contains(cube_points_after_rotation[7]) == true);

    cube.setRotation({0, 0, M_PI});

    CHECK(cube.contains(cube_points_after_rotation[0]) == true);
    CHECK(cube.contains(cube_points_after_rotation[1]) == true);
    CHECK(cube.contains(cube_points_after_rotation[2]) == true);
    CHECK(cube.contains(cube_points_after_rotation[3]) == true);
    CHECK(cube.contains(cube_points_after_rotation[4]) == true);
    CHECK(cube.contains(cube_points_after_rotation[5]) == true);
    CHECK(cube.contains(cube_points_after_rotation[6]) == true);
    CHECK(cube.contains(cube_points_after_rotation[7]) == true);

    cube.setRotation({M_PI, M_PI, M_PI});
    CHECK(cube.contains(cube_points_after_rotation[0]) == true);
    CHECK(cube.contains(cube_points_after_rotation[1]) == true);
    CHECK(cube.contains(cube_points_after_rotation[2]) == true);
    CHECK(cube.contains(cube_points_after_rotation[3]) == true);
    CHECK(cube.contains(cube_points_after_rotation[4]) == true);
    CHECK(cube.contains(cube_points_after_rotation[5]) == true);
    CHECK(cube.contains(cube_points_after_rotation[6]) == true);
    CHECK(cube.contains(cube_points_after_rotation[7]) == true);

    BoxCollider b2{
        Vector3{2.1, 0, 0}, 2, 2, 2};
    std::vector<Vector3> expected_points = {
        Vector3{0, 0, 0},
        Vector3{0, 0, 2},
        Vector3{0, 2, 0},
        Vector3{0, 2, 2},
        Vector3{2, 0, 0},
        Vector3{2, 0, 2},
        Vector3{2, 2, 0},
        Vector3{2, 2, 2}};
}