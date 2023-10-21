#pragma once
#include "../../Saint-Nec-Engine-Lib/src/architecture/Component.h"
#include "../../Saint-Nec-Engine-Lib/src/architecture/Vector3.hpp"

namespace Physics
{
    class SphereCollider : public saintNecEngine::Component
    {
        saintNecEngine::Vector3 _center;
        double _radius;

    public:
        SphereCollider(saintNecEngine::Vector3 center, double radius);
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