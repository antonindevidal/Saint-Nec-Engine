#pragma once
#include "architecture/Component.h"
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
        };
    }
}