// Entetes //---------------------------------------------------------------------------------------
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
        Vector3{3, 3, 2}
    };

    CHECK(cube1.hasPoint(cube1_points_list[0]) == true);

}

TEST_CASE("TEST BASIC COLLISION WITHOUT ROTATION")
{
    using namespace saintNecEngine;
    using namespace saintNecPhysics;
    const BoxCollider b1{
        Vector3{2, 2, 1}, 2, 2, 2};

    const BoxCollider b2{
        Vector3{3, 3, 1}, 2, 2, 2};
}
