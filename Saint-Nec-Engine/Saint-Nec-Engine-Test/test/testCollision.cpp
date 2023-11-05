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

// Tests //-----------------------------------------------------------------------------------------
using namespace sne;
using namespace saintNecPhysics;

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