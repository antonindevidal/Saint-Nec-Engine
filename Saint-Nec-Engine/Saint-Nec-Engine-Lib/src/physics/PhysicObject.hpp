#pragma once

/**
 * @file PhysicObject.hpp
 * @brief PhysicObject representive of the object in the game.
 * @author Abdeljalil ZOGHLAMI
 * @date november 17th 2023.
 */

#include "architecture/Component.hpp"
#include <glm/glm.hpp>

namespace sne
{
    namespace saintNecPhysics
    {
        /**
         * @paragraph Metrics
         * kg
         * m
         * s
         */
        using Forces = glm::vec3;
        class PhysicObject : public Component
        {
            glm::vec3 acceleration{0, 0, -9.81};
            glm::vec3 velocity{0, 0, 0};
            double mass; // kg
            float amortissement; // [0; 1]
            // To update with Component::parent
            glm::vec3 _position;
            glm::vec3 _rotation;
        public:

            /**
             * @brief Construct a new PhysicObject object positionned on origin
             * 
             */
            PhysicObject();
            ~PhysicObject() = default;

            /**
             * @brief Construct a new PhysicObject object positionned at
             * a defined point
             * 
             * @param position 
             */
            PhysicObject(const glm::vec3& position);

            /**
             * @brief applies a Force on the object
             * 
             */
            void applyForce(const Forces &);

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
        };
    }
}