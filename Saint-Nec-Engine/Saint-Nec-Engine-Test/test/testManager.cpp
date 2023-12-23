// Entetes //---------------------------------------------------------------------------------------
#include <iostream>
#include <catch.hpp>
#include <cmath>
#include <physics/SphereCollider.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <architecture/PhysicManager.hpp>
#include <chrono>

// Tests //-----------------------------------------------------------------------------------------
using namespace sne;
using namespace saintNecPhysics;

//--------------------------------------------------------------------------------------------------
TEST_CASE("TEST MANAGER - BASE 1")
{
    std::unique_ptr<PhysicManager> &p = PhysicManager::getInstance();
    std::vector<PhysicObject> v;
    std::vector<glm::vec3> positions;

    float width = 1;
    for (int i = 0; i < 100; i++)
    {
        PhysicObject o1{1};
        glm::vec3 center{i * (width + 0.5), 0, 0};
        o1.setPosition(center);
        o1.setAcceleration({0,0,0});
        BoxCollider *b = new BoxCollider{center, width, width, width};
        o1.setCollider(b);
        v.push_back(o1);
        positions.push_back(center);
    }

    for(auto &elt : v)
        p->addObject(&elt);
    

    p->update();

    // should have no collision and no movement
    auto start = std::chrono::high_resolution_clock::now();
    const std::vector<PhysicObject*> &objetcs = p->getObjects();
    for(int i=0; i<objetcs.size(); i++)
        CHECK( objetcs[i]->getPosition() == positions[i]);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Temps d'execution: " << duration.count() << "\n";
}

