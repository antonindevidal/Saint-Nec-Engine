#pragma once
/**
 * @file SphereCollider.hpp
 * @brief Sphere to detect collision.
 * @author Abdeljalil ZOGHLAMI, Antonin DEVIDAL.
 * @date november 6rd 2023.
 *
 */

#include "Collider.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace sne
{

    namespace saintNecPhysics
    {
        /**
         * @class SphereCollider
         * @brief SphereCollider physics component
         */
        class SphereCollider : public Collider
        {
        private:
            glm::vec3 _center;
            double _radius;

        public:
            SphereCollider(glm::vec3 center, double radius);
            ~SphereCollider() = default;

            /**
             * @brief Get the Radius object
             *
             * @return const double
             */
            const double getRadius() const;

            bool collide(const Collider*) const override;
            bool collide(const SphereCollider&) const override;
            bool collide(const BoxCollider&) const override;
        };
    }
}