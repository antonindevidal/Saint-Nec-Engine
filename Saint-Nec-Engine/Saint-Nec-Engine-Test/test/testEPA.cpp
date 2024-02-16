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
#include <physics/util.hpp>

// Tests //-----------------------------------------------------------------------------------------
using namespace sne;
using namespace physics;

// Data log file
const glm::vec3 initialDirection = {1, 0, 0};

/**************************************************************************************************/
/*                                    BOXCOLLIDER AND BOXCOLLIDER                                 */
/**************************************************************************************************/
TEST_CASE("TEST normal face")
{

    const BoxCollider b1{glm::vec3{0, 0, 0}, 2,2,2};

    const BoxCollider b2{glm::vec3{1.5, 0, 0}, 2,2,2};

    glm::vec3 expected1 = {1, 0, 0};

    CHECK(gjk(b1, b2, {1, 0, 0}) == true);

    const BoxCollider b3{glm::vec3{0, 0, 0}, 2,2,2};

    const BoxCollider b4{glm::vec3{0, 1.5, 0}, 2,2,2};

    glm::vec3 expected2 = {0, 1, 0};

    CHECK(gjk(b3, b4, {0, 1, 0}) == true);
}