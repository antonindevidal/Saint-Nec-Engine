#pragma once
#include "architecture/Component.hpp"
#include "architecture/Vector3.hpp"

namespace sne
{

    namespace saintNecPhysics
    {
        class SphereCollider : public Component
        {
        private:
            Vector3 _center;
            double _radius;

        public:
            SphereCollider(Vector3 center, double radius);
            ~SphereCollider() = default;
            const double getRadius() const;
            const Vector3& getCenter() const;
        };
    }
}