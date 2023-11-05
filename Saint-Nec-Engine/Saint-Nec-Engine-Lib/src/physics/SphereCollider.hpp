#pragma once
#include "architecture/Component.hpp"
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
        class SphereCollider : public Component
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
            
            /**
             * @brief Get the Center object
             * 
             * @return const Vector3& 
             */
            const glm::vec3 &getCenter() const;
        };
    }
}