#pragma once

/**
 * @file PhysicObject.hpp
 * @brief PhysicObject representation of the object in the game.
 * @author Abdeljalil ZOGHLAMI
 * @date november 17th 2023.
 */


#include <glm/glm.hpp>
#include <exception>
#include <architecture/Component.hpp>
#include <architecture/util.hpp>
#include <architecture/GameObject.hpp>
#include <architecture/Time.hpp>
#include "Collider.hpp"
#include "SphereCollider.hpp"
#include "BoxCollider.hpp"
#include "SAT.hpp"


namespace sne::physics
{
    /**
     * @paragraph Metrics
     * kg
     * m
     * s
     */
    using Force = glm::vec3;
    class PhysicObject : public Component
    {
        glm::vec3 _acceleration{0, -9.81, 0};
        glm::vec3 _velocity{0, 0, 0};
        float _mass = 1;          // kg
        float _amortissement = 1; // [0; 1] 1 -> elastic choc

        // To update with Component::parent
        glm::vec3 _position;
        glm::vec3 _rotation;
        Collider *_collider = nullptr;

        // To update with inheritence
        bool isFix = false;

        static Time* time; 

    public:
        bool hasBeenUpdated = false;
        
        /**
         * @brief Construct a new PhysicObject object positionned on origin
         *
         */
        PhysicObject(float mass);
        ~PhysicObject();

        /**
         * @brief Construct a new PhysicObject object positionned at
         * a defined point
         *
         * @param position
         */
        PhysicObject(const glm::vec3 &position, float mass);

        /************************************************************************/
        /*                      GETTER & SETTER                                 */
        /************************************************************************/
        const glm::vec3 &getAcceleration() const;
        const glm::vec3 &getVelocity() const;
        const glm::vec3 &getPosition() const;
        const glm::vec3 &getRotation() const;
        float getAmortissement() const;
        float getMass() const;
        const Collider * getCollider() const;

        void setAcceleration(const glm::vec3 &);
        void setVelocity(const glm::vec3 &);
        void setPosition(const glm::vec3 &);
        void setRotation(const glm::vec3 &);
        void setMass(float);
        void setCollider(Collider *collider);
        void fix()
        {
            isFix = true;
            setAcceleration({0,0,0});
            setVelocity({0,0,0});
        }
        /************************************************************************/

        /**
         * @brief applies a Force on the object
         * This one must be a constante force such as gravity
         *
         *
         * @param f force to apply, a vec3 representing both direction and intensity
         */
        void applyForce(const Force &f);

        /**
         * @brief update the object over the time
         *
         */
        void update() override;
        // Proposition: take a dt in argument for update

        /**
         * @brief update the object over a done time
         *
         * @param dt delta time
         */
        void compute(float dt);

        /**
         * @brief update the object considering interaction/choc with an over one.
         * When BOTH are mobile !
         *
         * @param obj mobile object with wich one we collide
         */
        void computeCollide(PhysicObject &obj); // Reflexion architecture, not ok like that

        class IllegalMassException : public std::exception
        {
        public:
            const char *what() const noexcept
            {
                return "Object must have a valide mass!";
            }
        };
    };

    void addImpulsion(PhysicObject &o1, PhysicObject &o2);
}