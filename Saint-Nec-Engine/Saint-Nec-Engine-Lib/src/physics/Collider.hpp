#pragma once
/**
 * @file Collider.hpp
 * @brief Collider interface.
 * @author Abdeljalil ZOGHLAMI, Antonin DEVIDAL.
 * @date november 23rd 2023.
 *
 */

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace sne
{
    namespace saintNecPhysics
    {
        class SphereCollider;
        class BoxCollider;

        class Collider
        {
        protected:
            glm::vec3 _center;
            double _radius;

        public:
            /**
             * @brief Get the Center object
             *
             * @return const vec3&
             */
            const glm::vec3 &getCenter() const
            {
                return _center;
            }

            void setCenter(const glm::vec3 &v)
            {
                _center = v;
            }

            virtual bool collide(const Collider*) const = 0;
            virtual bool collide(const SphereCollider&) const = 0;
            virtual bool collide(const BoxCollider&) const = 0;
        };
    }
}