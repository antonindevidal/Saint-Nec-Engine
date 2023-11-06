#pragma once
#include "architecture/Component.hpp"
#include "architecture/Vector3.hpp"

/**
 * @file SphereCollider.hpp
 * @brief Sphere to detect collision.
 * @author Abdeljalil ZOGHLAMI, Antonin DEVIDAL.
 * @date november 6rd 2023.
 *
 */

namespace sne
{

    namespace saintNecPhysics
    {
        /**
         * @class SphereCollider
         * @brief SphereCollider physics component
         */
        class SphereCollider : public Component
        {
        private:
            Vector3 _center;
            double _radius;

        public:
            SphereCollider(Vector3 center, double radius);
            ~SphereCollider() = default;

            /**
             * @brief Get the Radius object
             * 
             * @return const double 
             */
            const double getRadius() const;
            
            /**
             * @brief Get the Center object
             * 
             * @return const Vector3& 
             */
            const Vector3 &getCenter() const;
        };
    }
}