#pragma once

/**
 * @file PhysicObject.hpp
 * @brief PhysicObject representive of the object in the game.
 * @author Abdeljalil ZOGHLAMI
 * @date november 17th 2023.
 */

#include "architecture/Component.hpp"
#include <glm/glm.hpp>
#include <exception>

namespace sne
{
    const int FPS = 10;
    namespace saintNecPhysics
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
            glm::vec3 _acceleration{0, 0, -9.81};
            glm::vec3 _velocity{0, 0, 0};
            float _mass = 1;          // kg
            float _amortissement = 1; // [0; 1]

            // To update with Component::parent
            glm::vec3 _position;
            glm::vec3 _rotation;
            Component *_collider = nullptr;

        public:
            /**
             * @brief Construct a new PhysicObject object positionned on origin
             *
             */
            PhysicObject(float mass);
            ~PhysicObject() = default;

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

            void setAcceleration(const glm::vec3 &);
            void setVelocity(const glm::vec3 &);
            void setPosition(const glm::vec3 &);
            void setRotation(const glm::vec3 &);
            void setMass(float);
            void setCollider(Component *collider);
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
             * @brief update the object considering interaction/choque with an over one.
             * When BOTH are mobile !
             *
             * @param obj mobile object with wich one we collide
             */
            void computeCollide(PhysicObject &obj); // Reflexion architecture, not ok like that

            class IllegalMassException : public std::exception
            {
            public:
                const char* what() const noexcept
                {
                    return "Object must have a valide mass!";
                } 
            };
        };
    }
}