// Entetes //---------------------------------------------------------------------------------------
#include <iostream>
#include <catch.hpp>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <physics/PhysicObject.hpp>
#include <architecture/util.hpp>

// Tests //-----------------------------------------------------------------------------------------
using namespace sne;
using namespace saintNecPhysics;

//--------------------------------------------------------------------------------------------------
TEST_CASE("TEST PhysicObject 1")
{
    PhysicObject o{{0, 0, 9.81}, 1};

    o.compute(sqrt(2));

    REQUIRE(areSimilar(o.getPosition(), {0, 0, 0}));

    o.setPosition({0, 0, 0});
    o.setAcceleration({0, 0, 0});
    o.setVelocity({10, 0, 0});

    for (int i = 0; i < 11; i++)
    {
        CHECK(o.getPosition() == ((float)i * o.getVelocity()));
        o.compute(1);
    }

    REQUIRE(o.getPosition() == glm::vec3{110, 0, 0});
}

// Need collider before otherwise same center so no 'reaction' because no 'axis between' (direction)
TEST_CASE("TEST Newton Laws 1")
{
    glm::vec3 position1{0, 0, 0};
    glm::vec3 position2{100, 0, 0};

    PhysicObject o1{position1, 10};
    PhysicObject o2{position2, 10};

    // Cancel gravity
    o1.setAcceleration({0, 0, 0});
    o2.setAcceleration({0, 0, 0});
    
    o1.setVelocity({10, 0, 0});
    o2.setVelocity({-10, 0, 0});

    o1.compute(5);
    o2.compute(5);

    REQUIRE(o1.getPosition() == o2.getPosition());

    o1.computeCollide(o2);
    // glm::vec3 v1 = o1.getVelocity();
    // glm::vec3 v2 = o2.getVelocity();
    // CHECK(v1 == -v2);
    // o1.compute(5);
    // o1.compute(5);

    // REQUIRE(o1.getPosition() == position2);
    // REQUIRE(o2.getPosition() == position1);
}