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
    PhysicObject o{ {0, 0, 9.81} };

    std::cout << o.getPosition() << "\n";
    o.compute(sqrt(2));
    std::cout << o.getPosition() << "\n";

    REQUIRE(areSimilar(o.getPosition(), {0, 0, 0}));
}