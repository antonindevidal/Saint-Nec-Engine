#pragma once
#include "src/architecture/Component.h"
#include "src/architecture/Vector3.hpp"

namespace saintNecEngine
{

    namespace saintNecPhysics
    {
        class SphereCollider : public Component
        {
            Vector3 _center;
            double _radius;

        public:
            SphereCollider(Vector3 center, double radius);
            void update() override
            {
                // Je suis une fraude
            }

            void draw() const override
            {
                // Je suis une fraude
            }
        };
    }
}