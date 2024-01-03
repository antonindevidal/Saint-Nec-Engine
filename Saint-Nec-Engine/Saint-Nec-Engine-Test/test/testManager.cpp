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

// --------------------------------------------------------------------------------------------------
TEST_CASE("TEST MANAGER - BASE 1")
{
    std::unique_ptr<PhysicManager> &p = PhysicManager::getInstance();
    std::vector<PhysicObject*> v;
    std::vector<glm::vec3> positions;

    float width = 1;
    for (int i = 0; i < 100; i++)
    {
        PhysicObject *o1 = new PhysicObject{1};
        glm::vec3 center{i * (width + 0.5), 0, 0};
        o1->setPosition(center);
        o1->setAcceleration({0,0,0});
        BoxCollider *b = new BoxCollider{center, width, width, width};
        o1->setCollider(b);
        v.push_back(o1);
        positions.push_back(center);
    }

    for(auto elt : v)
        p->addObject(elt);
    

    p->update();

    // should have no collision and no movement
    const std::vector<PhysicObject*> &objetcs = p->getObjects();
    for(int i=0; i<objetcs.size(); i++)
        CHECK( objetcs[i]->getPosition() == positions[i]);

    p->clear();
}

TEST_CASE("TEST MANAGER TIME COMPARISON")
{
    std::unique_ptr<PhysicManager> &manager = PhysicManager::getInstance();
    PhysicObject *po = nullptr;
    Collider *collider = nullptr;
    
    // Full collision measure
    for(int i=0; i<100; i++)
    {
        glm::vec3 center = {0,0,0};
        po = new PhysicObject{center, 10};
        collider = new BoxCollider{center, 4, 4, 4};
        po->setAcceleration({0,0,0});
        po->setCollider(collider);
        manager->addObject(po);
    }

    auto start = std::chrono::high_resolution_clock::now();
    manager->computeCollision();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Temps d'execution collision total BoxCollider: " << duration.count() << "µs\n";
    manager->clear();

    // 0 collision measure
    for(int i=0; i<100; i++)
    {
        glm::vec3 center = {i*10,0,0};
        po = new PhysicObject{center, 10};
        collider = new BoxCollider{center, 4, 4, 4};
        po->setAcceleration({0,0,0});
        po->setCollider(collider);
        manager->addObject(po);
    }

    start = std::chrono::high_resolution_clock::now();
    manager->computeCollision();
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Temps d'execution 0 collision BoxCollider: " << duration.count() << "µs.\n";
    manager->clear();
}

