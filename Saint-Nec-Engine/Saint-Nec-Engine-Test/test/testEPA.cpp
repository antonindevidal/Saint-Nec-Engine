// Entetes //---------------------------------------------------------------------------------------
#define _USE_MATH_DEFINES
#include <iostream>
#include <catch.hpp>
#include <cmath>
#include <architecture/Component.hpp>
#include <architecture/util.hpp>
#include <physics/BoxCollider.hpp>
#include <physics/SphereCollider.hpp>
#include <physics/PhysicObject.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <physics/util.hpp>

// Tests //-----------------------------------------------------------------------------------------
using namespace sne;
using namespace physics;

/**************************************************************************************************/
/*                                    BOXCOLLIDER AND BOXCOLLIDER                                 */
/**************************************************************************************************/
// TEST_CASE("TEST normal face")
// {

//     glm::vec3 center1{0, 0, 0},
//               center2{1.5, 0, 0};
//     const BoxCollider b1{center1, 2,2,2};

//     const BoxCollider b2{center2, 2,2,2};

//     glm::vec3 normal;

//     std::cout << "Should not converge: ";
//     REQUIRE(gjk(b1, b2, normal));

//     glm::vec3 expected = {1, 0, 0};

//     PhysicObject p0{center1, 1},
//                  p1{center2, 1};
//     p0.setCollider(new BoxCollider{center1, 2,20,17});
//     p1.setCollider(new BoxCollider{center2, 2,2,2});

//     std::cout << "\nShould converge";
//     REQUIRE(gjk(*p0.getCollider(), *p1.getCollider(), normal));
//     std::cout << "\nnormal found: " << normal << " expected:" << expected << "\n";
// }

/**************************************************************************************************/
/*                                    BOXCOLLIDER AND SPHERECOLLIDER                              */
/**************************************************************************************************/
TEST_CASE("TEST 2 differents shapes")
{

    glm::vec3 center1{0, 0, 0},
        center2{1.5, 0, 0};

    glm::vec3 expected = {1, 0, 0};

    glm::vec3 normal;

    PhysicObject p0{center1, 1},
        p1{center2, 1},
        p2{center1, 1};

    p0.setCollider(new BoxCollider{center1, 2, 20, 17});
    p1.setCollider(new BoxCollider{center2, 2, 2, 2});
    p2.setCollider(new BoxCollider{center1, 2, 20, 17});

    // std::cout << "\nShould converge\n";
    // p0.fix();
    // std::cout << "gauche :" << p0.getPosition() << "\n";
    // std::cout << "droite :" << p1.getPosition() << "\n";
    // REQUIRE(gjk(*p0.getCollider(), *p1.getCollider(), normal));
    // p0.computeCollide(p1);
    // std::cout << "\nnormal found: " << normal << " expected:" << expected << "\n";

    // std::cout << "gauche :" << p0.getPosition() <<"\n";
    // std::cout << "droite :" << p1.getPosition() <<"\n";

    REQUIRE(gjk(*p2.getCollider(), *p1.getCollider(), normal));
    p2.computeCollide(p1);
}