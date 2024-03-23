// Entetes //---------------------------------------------------------------------------------------
#define _USE_MATH_DEFINES
#include <iostream>
#include <catch.hpp>
#include <cmath>
#include <architecture/Component.hpp>
#include <architecture/util.hpp>
#include <physics/BoxCollider.hpp>
#include <physics/SphereCollider.hpp>
#include <physics/SAT.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "logFile.hpp"
#include <physics/util.hpp>

// Tests //-----------------------------------------------------------------------------------------
using namespace sne;
using namespace physics;

// Data log file
const std::string filename = "collisionGJK.txt";
std::ofstream datafile = open(filename);
glm::vec3 normal;

/**************************************************************************************************/
/*                                    BOXCOLLIDER AND BOXCOLLIDER                                 */
/**************************************************************************************************/
TEST_CASE("TEST BOXCOLLIDER BASIC COLLISION WITHOUT ROTATION")
{

    const BoxCollider b1{
        glm::vec3{2, 2, 1}, 2, 2, 2};

    const BoxCollider b2{
        glm::vec3{3, 3, 1}, 2, 2, 2};

    const BoxCollider b3{
        glm::vec3{30, 30, 10}, 2, 2, 2};

    CHECK(gjk(b1, b2, normal) == true);
    CHECK(gjk(b1, b3, normal) == false);
    CHECK(gjk(b2, b3, normal) == false);
}

TEST_CASE("TEST BOXCOLLIDER BASIC COLLISION WITH ROTATION")
{
    BoxCollider b1{
        glm::vec3{0, 0, 0}, 2, 2, 2};

    BoxCollider b2{
        glm::vec3{2.1, 0, 0}, 2, 2, 2};

    REQUIRE(gjk(b1, b2, normal) == false);

    b2.setRotation(glm::vec3{0, M_PI / 4, 0});
    REQUIRE(gjk(b1, b2, normal) == true);
}

/**************************************************************************************************/
/*                                 SPHERECOLLIDER AND SPHERECOLLIDER                              */
/**************************************************************************************************/
TEST_CASE("TEST SPHERECOLLIDER BASIC COLLISION WITH ROTATION")
{
    const SphereCollider sphere1{glm::vec3{0, 0, 0}, 1};
    const SphereCollider sphere2{glm::vec3{2.1, 0, 0}, 1};
    const SphereCollider sphere3{glm::vec3{1.05, 0, 0}, 1};

    CHECK(gjk(sphere1, sphere2, normal) == false);
    CHECK(gjk(sphere1, sphere3, normal) == true);
    CHECK(gjk(sphere2, sphere3, normal) == true);
}

/**************************************************************************************************/
/*                                   BOXCOLLIDER AND SPHERECOLLIDER                               */
/**************************************************************************************************/
TEST_CASE("TEST SPHERECOLLIDER BASIC COLLISION WITH BOXCOLLIDER")
{
    const SphereCollider sphere1{glm::vec3{0, 0, 0}, 1};
    const SphereCollider sphere2{glm::vec3{2.1, 0, 0}, 1};
    const SphereCollider sphere3{glm::vec3{1.05, 0.5, 0}, 1};

    BoxCollider boxe1{glm::vec3{0, 0, 0}, 2, 2, 2};

    CHECK(gjk(sphere1, boxe1, normal) == true);
    CHECK(gjk(sphere2, boxe1, normal) == false);
    CHECK(gjk(sphere3, boxe1, normal) == true);

    boxe1.setRotation({0, M_PI / 4, 0});
    CHECK(gjk(sphere2, boxe1, normal) == true);
}

const double width = 2,
             height = 2,
             depth = 2;

TEST_CASE("MULTIPLE TEST FROM SOLIDWORKS DATA")
{
    glm::vec3 center1 = {0, 0, 0},
              center2;
    BoxCollider box1{center1, width, depth, height},
        box2{center1, width, depth, height};

    // Data 1
    // Axe X
    center2 = center1 + glm::vec3{2, 2, 4};
    box2.setCenter(center2);
    REQUIRE(gjk(box1, box2, normal) == false);
    // Axe Y
    center2 = center1 + glm::vec3{4, 2, 2};
    box2.setCenter(center2);
    REQUIRE(gjk(box1, box2, normal) == false);
    // Axe Z
    center2 = center1 + glm::vec3{2, 4, 2};
    box2.setCenter(center2);
    REQUIRE(gjk(box1, box2, normal) == false);

    // Data 2
    // Axe X
    center2 = center1 + glm::vec3{2, 2, 1};
    box2.setCenter(center2);
    REQUIRE(gjk(box1, box2, normal) == true);
    // Axe Y
    center2 = center1 + glm::vec3{1, 2, 2};
    box2.setCenter(center2);
    REQUIRE(gjk(box1, box2, normal) == true);
    // Axe Z
    center2 = center1 + glm::vec3{2, 1, 2};
    box2.setCenter(center2);
    REQUIRE(gjk(box1, box2, normal) == true);

    // Data 3
    // Axe X
    center2 = center1 + glm::vec3{1, 1, 2};
    box2.setCenter(center2);
    REQUIRE(gjk(box1, box2, normal) == true);
    // Axe Y
    center2 = center1 + glm::vec3{1, 2, 1};
    box2.setCenter(center2);
    REQUIRE(gjk(box1, box2, normal) == true);
    // Axe Z
    center2 = center1 + glm::vec3{2, 1, 1};
    box2.setCenter(center2);
    REQUIRE(gjk(box1, box2, normal) == true);

    // Avec des rotations
    // Data 4
    center2 = center1 + glm::vec3{2, 2, 2};
    box2.setCenter(center2);
    box2.setRotation({0, M_PI / 4, 0});
    REQUIRE(gjk(box1, box2, normal) == false);

    center2 = center1 + glm::vec3{2, 1, 1};
    box2.setCenter(center2);
    box2.setRotation({0, M_PI / 4, 0});
    REQUIRE(gjk(box1, box2, normal) == true);

    // Avec des spheres
    SphereCollider sphere{center2, 1};

    // Data 5
    // Axe X
    center2 = center1 + glm::vec3{1, 1, 2};
    sphere.setCenter(center2);
    REQUIRE(gjk(box1, sphere, normal) == true);
    // Axe Y
    center2 = center1 + glm::vec3{1, 2, 1};
    sphere.setCenter(center2);
    REQUIRE(gjk(box1, sphere, normal) == true);
    // Axe Z
    center2 = center1 + glm::vec3{2, 1, 1};
    sphere.setCenter(center2);
    REQUIRE(gjk(box1, sphere, normal) == true);

    // Data 6
    // Axe X
    center2 = center1 + glm::vec3{1, 1, 3};
    sphere.setCenter(center2);
    REQUIRE(gjk(box1, sphere, normal) == false);
    // Axe Y
    center2 = center1 + glm::vec3{1, 3, 1};
    sphere.setCenter(center2);
    REQUIRE(gjk(box1, sphere, normal) == false);
    // Axe Z
    center2 = center1 + glm::vec3{3, 1, 1};
    sphere.setCenter(center2);
    REQUIRE(gjk(box1, sphere, normal) == false);

    // Data 7
    // Axe X
    center2 = center1 + glm::vec3{1, 1, 1};
    sphere.setCenter(center2);
    REQUIRE(gjk(box1, sphere, normal) == true);
    // Axe Y
    center2 = center1 + glm::vec3{1, 1, 1};
    sphere.setCenter(center2);
    REQUIRE(gjk(box1, sphere, normal) == true);
    // Axe Z
    center2 = center1 + glm::vec3{1, 1, 1};
    sphere.setCenter(center2);
    REQUIRE(gjk(box1, sphere, normal) == true);
}