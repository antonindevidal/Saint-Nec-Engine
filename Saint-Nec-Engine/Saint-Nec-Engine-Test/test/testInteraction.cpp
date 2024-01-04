// Entetes //---------------------------------------------------------------------------------------
#define _USE_MATH_DEFINES
#include <iostream>
#include <catch.hpp>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <physics/PhysicObject.hpp>
#include <architecture/util.hpp>
#include "logFile.hpp"

// Tests //-----------------------------------------------------------------------------------------
using namespace sne;
using namespace physics;

const std::string filename = "testInteraction.txt";

//--------------------------------------------------------------------------------------------------
TEST_CASE("TEST PhysicObject 1")
{
    PhysicObject o{{0, 9.81, 0}, 1};

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

    try
    {
        o1.computeCollide(o2);
        FAIL();
    }
    catch (const std::exception_ptr &e)
    {
        CHECK("No collider associed, checked" != "");
        std::cout << "No collider associed\n";
    }


    glm::vec3 v1 = o1.getVelocity();
    glm::vec3 v2 = o2.getVelocity();

    CHECK(v1 == -v2);
    o1.compute(5);
    o2.compute(5);

    REQUIRE(o1.getPosition() == position2);
    REQUIRE(o2.getPosition() == position1);
}

TEST_CASE("TEST Collider cohesion")
{
    glm::vec3 center{0, 0, 0};
    PhysicObject o1{center, 10};
    PhysicObject o2{center, 10};

    SphereCollider *sphere = new SphereCollider{center, 10};
    BoxCollider *box = new BoxCollider{center, 10, 10, 10};

    o1.setCollider(sphere);
    o2.setCollider(box);

    o1.compute(5);
    o2.compute(5);

    CHECK(o1.getPosition() != glm::vec3{0, 0, 0});
    CHECK(o2.getPosition() != glm::vec3{0, 0, 0});
    CHECK(o1.getPosition() == sphere->getCenter());
    CHECK(o2.getPosition() == box->getCenter());

    o1.setAcceleration({0, 0, 0});
    o2.setAcceleration({0, 0, 0});

    o1.setPosition({0, 0, 0});
    o2.setPosition({0, 0, 0});

    o1.setVelocity({1, 2, 3});
    o2.setVelocity({-1, -2, -3});

    float sum_dt = 0;
    for (int i = 0; i < 101; i++)
    {
        o1.compute(i);
        o2.compute(i);

        sum_dt += i;
        glm::vec3 p1 = sum_dt * o1.getVelocity();
        glm::vec3 p2 = sum_dt * o2.getVelocity();

        CHECK(o1.getPosition() == p1);
        CHECK(o2.getPosition() == p2);
    }

    o1.setVelocity({0, 0, 0});
    o2.setVelocity({0, 0, 0});

    o1.setPosition({0, 0, 0});
    o2.setPosition({0, 0, 0});

    o1.setAcceleration({1, 2, 3});
    o2.setAcceleration({-1, -2, -3});

    sum_dt = 0;
    for (int i = 0; i < 93; i++)
    {
        o1.compute(i);
        o2.compute(i);

        sum_dt += i;
        glm::vec3 p1 = (float)0.5 * sum_dt * sum_dt * o1.getAcceleration();
        glm::vec3 p2 = (float)0.5 * sum_dt * sum_dt * o2.getAcceleration();

        CHECK(o1.getPosition() == p1);
        CHECK(o2.getPosition() == p2);
    }
}

TEST_CASE("TEST GRAVITY WITH CHART")
{
    std::ofstream dataFile = open(filename);

    glm::vec3 center{0, 0, 0};
    PhysicObject o1{center, 10};
    SphereCollider *sphere = new SphereCollider{center, 10};

    o1.setCollider(sphere);

    dataFile << "1\n";
    schriben(dataFile, o1.getPosition());

    for (int i = 0; i < 10; i++)
    {
        o1.compute(1);
        schriben(dataFile, o1.getPosition());
    }

    dataFile.close();
}

TEST_CASE("TEST TOTAL CHART INTERACTION")
{
    std::ofstream dataFile = open(filename);

    glm::vec3 center{0, 0, 0};
    PhysicObject o1{center, 10};
    SphereCollider *sphere = new SphereCollider{center, 10};

    glm::vec3 center2{0, 0, 100};
    PhysicObject o2{center2, 10};
    SphereCollider *sphere2 = new SphereCollider{center2, 10};

    o1.setCollider(sphere);
    o2.setCollider(sphere2);

    o1.setAcceleration({0, 0, 0});
    o2.setAcceleration({0, 0, -9.81});
    
    float dt = 0.2;
    dataFile << dt << "\n";
    schriben(dataFile, o2.getPosition());
    for (int i = 0; i < 30; i++)
    {
        o1.compute(dt);
        o2.compute(dt);
        std::cout << o1.getPosition() <<"\n";
        std::cout << o2.getPosition() <<"\n";
        o1.computeCollide(o2);
        // std::cout << o2.getPosition() <<"\n";
        schriben(dataFile, o2.getPosition());
    }

    dataFile.close();
}
