// Entetes //---------------------------------------------------------------------------------------
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

// Tests //-----------------------------------------------------------------------------------------
using namespace sne;
using namespace saintNecPhysics;

// Data log file
const std::string filename = "collision.txt";
std::ofstream datafile = open(filename);

//--------------------------------------------------------------------------------------------------
TEST_CASE("TEST NORM")
{

    glm::vec3 v1 = {0, 0, 0};
    glm::vec3 v2 = {1, 0, 0};
    glm::vec3 v3 = {3, 4, 0};

    CHECK(norm(v1) == Approx(0.0));
    CHECK(norm(v2) == Approx(1.0));
    CHECK(norm(v3) == Approx(5.0));
}

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

    CHECK(hasSATCollision(b1, b2) == true);
    CHECK(hasSATCollision(b1, b3) == false);
    CHECK(hasSATCollision(b2, b3) == false);
}

TEST_CASE("TEST BOXCOLLIDER BASIC COLLISION WITH ROTATION")
{
    BoxCollider b1{
        glm::vec3{0, 0, 0}, 2, 2, 2};

    BoxCollider b2{
        glm::vec3{2.1, 0, 0}, 2, 2, 2};

    CHECK(hasSATCollision(b1, b2) == false);

    b2.setRotation(glm::vec3{0, M_PI / 4, 0});
    CHECK(hasSATCollision(b1, b2) == true);
}

/**************************************************************************************************/
/*                                 SPHERECOLLIDER AND SPHERECOLLIDER                              */
/**************************************************************************************************/
TEST_CASE("TEST SPHERECOLLIDER BASIC COLLISION WITH ROTATION")
{
    const SphereCollider sphere1{glm::vec3{0, 0, 0}, 1};
    const SphereCollider sphere2{glm::vec3{2.1, 0, 0}, 1};
    const SphereCollider sphere3{glm::vec3{1.05, 0.5, 0}, 1};

    CHECK(hasSATCollision(sphere1, sphere2) == false);
    CHECK(hasSATCollision(sphere1, sphere3) == true);
    CHECK(hasSATCollision(sphere2, sphere3) == true);
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

    CHECK(hasSATCollision(sphere1, boxe1) == true);
    CHECK(hasSATCollision(sphere2, boxe1) == false);
    CHECK(hasSATCollision(sphere3, boxe1) == true);

    boxe1.setRotation({0, M_PI / 4, 0});
    CHECK(hasSATCollision(sphere2, boxe1) == true);
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
    REQUIRE(hasSATCollision(box1, box2) == false);
    // Axe Y
    center2 = center1 + glm::vec3{4, 2, 2};
    box2.setCenter(center2);
    REQUIRE(hasSATCollision(box1, box2) == false);
    // Axe Z
    center2 = center1 + glm::vec3{2, 4, 2};
    box2.setCenter(center2);
    REQUIRE(hasSATCollision(box1, box2) == false);

    // Data 2
    // Axe X
    center2 = center1 + glm::vec3{2, 2, 1};
    box2.setCenter(center2);
    REQUIRE(hasSATCollision(box1, box2) == true);
    // Axe Y
    center2 = center1 + glm::vec3{1, 2, 2};
    box2.setCenter(center2);
    REQUIRE(hasSATCollision(box1, box2) == true);
    // Axe Z
    center2 = center1 + glm::vec3{2, 1, 2};
    box2.setCenter(center2);
    REQUIRE(hasSATCollision(box1, box2) == true);

    // Data 3
    // Axe X
    center2 = center1 + glm::vec3{1, 1, 2};
    box2.setCenter(center2);
    REQUIRE(hasSATCollision(box1, box2) == true);
    // Axe Y
    center2 = center1 + glm::vec3{1, 2, 1};
    box2.setCenter(center2);
    REQUIRE(hasSATCollision(box1, box2) == true);
    // Axe Z
    center2 = center1 + glm::vec3{2, 1, 1};
    box2.setCenter(center2);
    REQUIRE(hasSATCollision(box1, box2) == true);


    // Avec des rotations
    // Data 4
    center2 = center1 + glm::vec3{2, 2, 2};
    box2.setCenter(center2);
    box2.setRotation({0, M_PI/4, 0});
    REQUIRE(hasSATCollision(box1, box2) == false);

    center2 = center1 + glm::vec3{2, 1, 1};
    box2.setCenter(center2);
    box2.setRotation({0, M_PI/4, 0});
    REQUIRE(hasSATCollision(box1, box2) == true);

    // Avec des spheres
    SphereCollider sphere{center2, 1};

    // Data 5
    // Axe X
    center2 = center1 + glm::vec3{1, 1, 2};
    sphere.setCenter(center2);
    REQUIRE(hasSATCollision(box1, sphere) == true);
    // Axe Y
    center2 = center1 + glm::vec3{1, 2, 1};
    sphere.setCenter(center2);
    REQUIRE(hasSATCollision(box1, sphere) == true);
    // Axe Z
    center2 = center1 + glm::vec3{2, 1, 1};
    sphere.setCenter(center2);
    REQUIRE(hasSATCollision(box1, sphere) == true); 

    // Data 6
    // Axe X
    center2 = center1 + glm::vec3{1, 1, 3};
    sphere.setCenter(center2);
    REQUIRE(hasSATCollision(box1, sphere) == false);
    // Axe Y
    center2 = center1 + glm::vec3{1, 3, 1};
    sphere.setCenter(center2);
    REQUIRE(hasSATCollision(box1, sphere) == false);
    // Axe Z
    center2 = center1 + glm::vec3{3, 1, 1};
    sphere.setCenter(center2);
    REQUIRE(hasSATCollision(box1, sphere) == false); 

    // Data 7
    // Axe X
    center2 = center1 + glm::vec3{1, 1, 1};
    sphere.setCenter(center2);
    REQUIRE(hasSATCollision(box1, sphere) == true);
    // Axe Y
    center2 = center1 + glm::vec3{1, 1, 1};
    sphere.setCenter(center2);
    REQUIRE(hasSATCollision(box1, sphere) == true);
    // Axe Z
    center2 = center1 + glm::vec3{1, 1, 1};
    sphere.setCenter(center2);
    REQUIRE(hasSATCollision(box1, sphere) == true); 

}